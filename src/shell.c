//
//  main.c
//  Created by Praneet Singh on 2/19/18.
//  Copyright © 2018 Praneet. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAXLINE 80 /* The maximum length command */


int main(void)
{
    pid_t pid;
    char *args[MAXLINE/2 + 1]; /* command line with max 40 arguments */
    char read[MAXLINE];			/*Holds the chars entered by user */
    int should_run = 1; /* flag to determine when to exit program */

    printf("CS149 Shell from Praneet Singh\n"); /* replace w/ name */

    while (should_run) {

        int i = 0;						// index i
        int parentWait = 1;				// if user enters '&' value will be set to 0

        printf("Praneet-897> "); /* prompt- replace FirstName and L3SID */
        fgets(read, MAXLINE, stdin);	// Gets input from teh user

        fflush(stdout);

        char *p = strtok(read,"\n ");	// Since fgets ends with a \n char, tokenize with "\n "

        while(p != NULL){				// while the chars are not NULL keep tokenizing
        	args[i] = p;
        	i++;
        	p = strtok(NULL,"\n ");
        }
        	args[i] = NULL;	// sets the value of i++ to NULL

        int j = 0;
        while(args[j] != NULL){			// loop checks if user entered '&'
        if(strcmp(args[j], "&") == 0){
            parentWait = 0;				// parentWait is set to 0
            args[j] = NULL;				// the location of '&' is set to NULL
          }
              j++;
          }
        if(strcmp(args[0], "exit") == 0){	// if user enters "exit", should_run is set to 0 and program exits.
        	should_run = 0;
        	exit(0);
        }
        /* After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will NOT invoke wait()
         */
       pid = fork();

       if(pid < 0){				// if the fork failed
    	   fprintf(stderr, "fork failed!\n");
    	   exit(1);
       }
       else if (pid == 0){		// if child process
        	execvp(args[0], args);
        	fprintf(stderr, "exec failed!\n");
        	exit(1);

        }
        else if(pid > 0){		// if parent process
        	if(parentWait){		// if user entered & parent will wait
        		wait(0);
        	}
        }

    }
    return 0;
}
