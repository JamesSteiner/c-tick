// jas330  watermark=ddbc7261cf9fbdc91b8a076ba6ae95b7
/* client.c */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {

  int sockfd;
  struct sockaddr_in servadr;

  if (argc != 3) {
    perror("Usage: client <host> <port>");
    return 1;
  }

  if ((sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0) {
    perror("Cannot create socket");
    return 2;
  }

  memset(&servadr,0,sizeof(servadr)); //typo - variable is serveradr, not serveraddr
  servadr.sin_family = AF_INET;
  servadr.sin_addr.s_addr = inet_addr(argv[1]); //again this should be sin_addr
                                                //not addr_sin
  servadr.sin_port = htons(atoi(argv[2]));

  if (connect(sockfd,(struct sockaddr *) &servadr,sizeof(servadr)) < 0) { //another typo:
                                                                           //should be serveradr
    perror("Cannot connect to server");
    return 3;
  }

  {
    int n;
    char bytes[BUFSIZE-1];
    while((n = read(sockfd,bytes,BUFSIZE)) > 0) {
      fwrite(bytes,n,sizeof(char),stdout);
    }
  }

  return 1;
}
// jas330  watermark=ddbc7261cf9fbdc91b8a076ba6ae95b7
