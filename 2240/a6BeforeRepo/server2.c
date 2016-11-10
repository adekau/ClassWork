 
/* 
     How can we handle more than one connection ? 
     Let's do some science ? I think we are going to 
     listen , listen, listen, and accept what we wish 
     with new process or thread 
*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define BufferSize 1024
void error(char *); // prototype 
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen,Connect_Count=0;
     char buffer[BufferSize]; // for communicating with client
     pid_t pid;int BufferNdx; // 
    FILE * F;
    struct stat S;// to find file length 
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     // some buffering for the child process
     char * TmpBuffer, *SavePtr, *FileName, *GetToken;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     memset( (char *) &serv_addr, 0, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
while (Connect_Count < 10)
{     listen(sockfd,5);
      clilen = sizeof(cli_addr);
      newsockfd = 
          accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) // exit server 
          error( "ERROR on accept");
     // otherwise let's fork 
     pid = fork();
     if (pid < 0) error("bad fork\n");
     if (pid == 0) break; // to handle talking with client below
// if parent loop again ? 
 }    

     memset(buffer, 0, BufferSize);
    
     memset(buffer, 0, BufferSize);n = read(newsockfd,buffer,BufferSize-1);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     printf("%s\n",(TmpBuffer=strtok_r(buffer,"\n",&SavePtr)));
     GetToken = strtok_r(TmpBuffer," ",&SavePtr); 
     printf("%s\n",GetToken);BufferNdx = 0;
    GetToken = strtok_r(NULL," ",&SavePtr); 
     printf("%s After Get\n",GetToken);GetToken++;
// now open the file and send it to client ? 
     if ((F =  fopen(GetToken,"r")) == NULL) error("Bad Dog\n");
            else printf("Good Dog\n"); 
    int N,FileSize;
        write(newsockfd,"HTTP/1.0 200 OK\\13\\10",17);
        write(newsockfd,"Content-Length:",15);
       fstat(fileno(F),&S);char MySize[10];MySize[9]=0;
       FileSize = S.st_size;
       sprintf(MySize,"%d",FileSize);
       fprintf(stderr,"size?%s\n",MySize);
       write(newsockfd,MySize,strlen(MySize));
        write(newsockfd,"\\13\\10",2);
        write(newsockfd,"Content-Type: image/jpeg\\13\\10",27);

     while (! feof(F))
     {N = fread((void *)buffer,1,BufferSize-1,F);
      write(newsockfd,buffer,N);
     }
      
     //n = write(newsockfd,"I got your message\n May I have another\n",40);
     if (n < 0) error("ERROR writing to socket");
     
     //write(newsockfd,"Ok, I am quitting\n",18);
     close(newsockfd);
     return 0; 
}

void error(char *msg)
{
    perror(msg);
    exit(1);
}


