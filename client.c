#include "common.h"

int main(int argc, char** argv) {
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    if (argc != 2) {
       fprintf(stderr, "USAGE: a.out <IPaddress>\n"); 
       exit(EXIT_FALIURE);
    }
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket error.\n");
        exit(EXIT_FALIURE);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // daytime server port
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]); 
        exit(EXIT_FALIURE);
    }
    
    if ( ( connect(sockfd,(SA*) &servaddr, sizeof(servaddr)) ) < 0) {
        fprintf(stderr, "connect error.\n");
        exit(EXIT_FALIURE);
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            fprintf(stderr, "fputs error.\n");
            exit(EXIT_FALIURE);
        }
    }
    if (n < 0) {
        fprintf(stderr, "read error.\n");
        exit(EXIT_FALIURE);
    }
   
    exit(EXIT_SUCCESS);
}
