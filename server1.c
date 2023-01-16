// jas330  watermark=ddbc7261cf9fbdc91b8a076ba6ae95b7
/* server.c */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXOPEN 5
#define BUFSIZE 1024

// accepts two arguments - 1) the port, and 2) the file
int main(int argc, char *argv[]) {

  int listenfd, connfd;
  FILE *fp;
  struct sockaddr_in server;

  // check that there are two arguments and that the second argument is a
  // path to a readable file
  if (argc != 3) {
    printf("%d", argc);
    puts("Usage: server <port> <file>");
    return 1;
  }

  if ((fp=fopen(argv[2],"rb")) == 0) {
    perror("Cannot find file to serve");
    return 2;
  }

  // configure server for port
  memset(&server,0,sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY); //first error - sin_addr instead
  server.sin_port = htons(atoi(argv[1]));

  // attach socket to the port
  if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("Cannot create server socket");
    return 3;
  }

  if (bind(listenfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("Cannot open the interface");
    return 4;
  }

  if (listen(listenfd,MAXOPEN) < 0) {
    perror("Cannot listen on the interface");
    return 5;
  }

  //for(;;) { //what is this doing here?

    if ( (connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) < 0 ) {
      perror("Error accepting a client connection");
      return 6;
    }

    while(!feof(fp)) {
      char bytes[BUFSIZE];
      int r=0,w=0;

      r = fread(bytes,sizeof(char),BUFSIZE,fp);

      while(w<r) {
        int total = write(connfd,bytes,r);
        if (total < 0) {
          perror("Error writing data to client");
          return 7;
          }
        w+=total;
      }
    }
    fseek(fp,0,SEEK_SET);

    close(connfd);

    return 0;
}
// jas330  watermark=ddbc7261cf9fbdc91b8a076ba6ae95b7
