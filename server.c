#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

void serviceClient(int);

int main(int argc, char *argv[]){  
  int sd, acpt, portNumber;
  struct sockaddr_in servAdd;     // server socket address
  if(argc != 2)
  {
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }
  
  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);
  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 3); // maximum 3 connect requests in queue

  while(1)
  {
    acpt = accept(sd, NULL, NULL);
    printf("Got a client\n\n\n");

    if(!fork())
    	serviceClient(acpt);
    close(acpt);
  }
}


void serviceClient(int sd)
{
  char putfile[255];
  char *input[2];
  char *fmsg1,*fmsg2,*fmsg3,*fmsg4;;
  FILE *fp;
  char file[255];
  int fd,i=0;
  char *token1;
  char *token2;
  
  // infinite loop of message exchange
  while(1)
  {
    if(read(sd, file, 255)<=0)
    {
      printf("\n\nBye Bye\n");
      close(sd);
      exit(0);
    }
    token1 = strtok(file, " ");
    while(token1!=NULL)
    {
      input[i]=token1;
      //printf("%s\n",token1);
      token1=strtok(NULL,"\n");
      i++;
    }

	// invalid user input	
    if(((strcmp(input[0],"get"))!=0)&&((strcmp(input[0],"put"))!=0))
    {
      printf("\n\nWrong Input By User\n");
    }
    
    // file upload request by user
    else if((strcmp(input[0],"put"))==0)
    {
      if(read(sd,putfile,255)<=0)
      {
        printf("\n\nDid not get reply from client\n");
      }
      if((strcmp(putfile,"$"))==0)
      {
        printf("\n\nDid not recieve file to upload\n");
      }
      else
      {
		int fd=open(input[1],O_WRONLY|O_CREAT|O_TRUNC,0700);
		write(fd,putfile,strlen(putfile)+1);
		close(fd);
		fmsg2="File Uploaded\n";
		write(sd,fmsg2,strlen(fmsg2)+1);
		printf("\n\n%s",fmsg2);
	  }
    }
    
    // file download request by user
    else if((strcmp(input[0],"get"))== 0)
    {
		if((fp = fopen(input[1],"r"))==NULL)
		{
	          printf("\n\nNo such file exists\n");
		  fmsg3="$";
		  write(sd,fmsg3,strlen(fmsg3)+1);
		} 
		else
		{
		  int len;
		  char filec[255];
		  fseek(fp,0,SEEK_END);
		  len=ftell(fp);
		  fseek(fp,0,SEEK_SET);
		  fread(filec,len,1,fp);
		  fclose(fp);
		  filec[len]='\0';
		  //printf("%s\n",filec);
		  write(sd,filec,strlen(filec)+1);
		  printf("file sent to client\n");
		}
    }
  }
}

