/* main.c - The foo shell

   Copyright (c) 2019 <project-developers>

   This file is part of <project-name>

   <project-name> is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdlib.h>
#include <stdio.h>
#include <config.h>

#ifndef HAVE_POSIXEG 
#error *** This example needs libposixeg (do you need CPPFLAGS/LDFLAGS?)
#endif

#include <posixeg/tparse.h>	/* We're using POSIXeg's parser. */
#include <posixeg/debug.h>	/* We're using POSIXeg's debug macros. */

#define PROMPT "@:"		/* You may change this prompt.  */

int go_on = 1;			/* This variable controls the main loop. */

int main (int argc, char **argv)
{
  int i, j, aux;

  /* This example uses libposixeg's trivial parser, which implements
     foosh grammar. Please, see documentation in posixeg/lib/tparser.h.
     You are free to either use this library or implement the parser yourself.
  */

  buffer_t *command_line;
  pipeline_t *pipeline;

  command_line = new_command_line (); /* An arbitrarily long command line. */

  pipeline = new_pipeline ();	/* A tree-like structure. */

  /* This is the main loop. */

  while (go_on)
    {
      /* Show prompt and read the command line. */

      printf ("%s ", PROMPT);
      fflush (stdout);
      aux = read_command_line (command_line);
      sysfatal (aux<0);

      /* Parse command line. */

      if (!parse_command_line (command_line, pipeline))
	{

	  /* This is an example, of how to use pipeline_t. 
	     See tparse.h for detailed information. */

	  printf ("  Pipeline has %d command(s)\n", pipeline->ncommands);

	  for (i=0; pipeline->command[i][0]; i++)
	    {
	      printf ("  Command %d has %d argument(s): ", i, pipeline->narguments[i]);
	      for (j=0; pipeline->command[i][j]; j++)
		printf ("%s ", pipeline->command[i][j]);
	      printf ("\n");
	    }
	  

	  if ( RUN_FOREGROUND(pipeline))
	    printf ("  Run pipeline in foreground\n");
	  else
	    printf ("  Run pipeline in background\n");

	  
	  
	  if ( REDIRECT_STDIN(pipeline))
	    printf ("  Redirect input from %s\n", pipeline->file_in);
	  if ( REDIRECT_STDOUT(pipeline))
	    printf ("  Redirect output to  %s\n", pipeline->file_out);

	  /* Don't forget to handle SIGINT and SIGTSTOP properly so that
	     the job, not the shell itself, be interrupted or suspended
	     by terminal character signals (Control-C, Control-Z).

	     see sigaction(). 

	     Tip: when block at read (prompting), a signal may unblock
	     the process. It's convenient to have the read call within
	     a loop which reissue read (p.ex. check errrno).

	  */
	  
	  /* This is where we would fork & exec. 

	     For a trivial implementation of a single-command execution,
	     parent process calls wait and blocks until a child terminates 
	     (receives a SIGCHLD). On background execution, parent does
	     not block a prompts the user again. In this case, a properly
	     configure signal handler should catch eventual SIGCHLD signals
	     to collect defunct process' data.

	        see wait(), waipid(), sigaction()

	     The child process puts itself in a newly created process group.
	     When command is a pipeline, all processes in the pipeline are
	     assigned the same process group, forming a job.
	     In foreground mode, terminal control should be assigned to the
	     job; in background mode terminal control should remain with
	     the shell process.
	     
	        see tcsetpgid(), tcsetpgrp()

	     If there is redirection (I/O or pipe), take care or this.

                see dup(), close()

	     Job is put in the job list. Built in commands jobs, fg, bg,
	     as well as SIGCHLD update this list accordingly.

	     If SIGINT and SIGTSTOP were ignored before, reset the default
	     behavior.

	     Child process then calls exec and runs the selected command. 

	        see execvp()
	   */

	  /* Tips.

	     See "Job Control" section of GNU Libc manual at 
             https://www.gnu.org/software/libc/manual/html_mono/libc.html#Job-Control

	     There are several examples of setting terminal control, pipeline
	     implementation (both recursive and iterative), fork & exec, 
	     signal handling etc. at posixeg/examples/snippets.

	   */

	}
    }

  release_command_line (command_line);
  release_pipeline (pipeline);

  return EXIT_SUCCESS;
}
