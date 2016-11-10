int redirect(int redirect_type, int prev_stdin, char ** argv, char * filename) {
  int returnfd;
  int status;
  pid = fork();
  if(pid < 0) err_sys("Error creating child process ");
  if(pid == 0) {
  	if(redirect_type == REDIRECT_STDOUT) {
  	  int fd0;
  	  if((fd0 = creat(filename, 0644)) < 0) err_sys("Error creating file ");

  	  if(prev_stdin != 0) dup2(prev_stdin, STDIN_FILENO);
  	  dup2(fd0, STDOUT_FILENO);
  	  close(fd0);
  	} else {
  	  int fd1 = open(filename, O_RDONLY);
  	  if(prev_stdin != 0) {
  	    pid = fork();
  	    if(pid < 0) err_sys("Error creating child process ");
  	    if(pid == 0) {
 		  dup2(prev_stdin, STDIN_FILENO);
 		  if(execvp(argv[0], argv) == -1) err_sys("Error executing command "); 
  	    }else{
  	      close(prev_stdin);
  	      waitpid(pid, &status, 0);
  	  	}
  	  	dup2(fd1, STDIN_FILENO);
  	  }else{
  	    dup2(fd1, STDIN_FILENO);
  	  }
  	  close(fd1);
  	}
  	returnfd = dup(STDOUT_FILENO);
  	if(execvp(argv[0], argv) == -1) err_sys("Error executing command ");
  }
  if(redirect_type == REDIRECT_STDOUT) returnfd = open(filename, O_RDONLY);
  waitpid(pid, &status, 0);
  return returnfd;
}
