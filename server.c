#include "common.h"
#include <time.h>

int main(int argc, char** argv) {
    int     listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buf[MAXLINE];
    time_t ticks;

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        handle_errors("error listen.\n");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // daytime server
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( (bind(listenfd, (SA*) &servaddr, sizeof(servaddr))) == -1)
        handle_errors("bind error.\n");

    Listen(listenfd, LISTENQ);

    while (true) {
        len = sizeof(cliaddr);
        if (accept(listenfd, (SA*) &cliaddr, &len) == -1)
            handle_errors("Cannot accept connection.\n");
        
        bzero(buf, sizeof(buf));
        if ( inet_ntop(AF_INET, &(cliaddr.sin_addr), buf, sizeof(buf)) == NULL) 
            handle_errors("inet_ntop error.\n");

        printf("\nConnection from %s, port %d\n", buf, ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        
        if (write(connfd, buf, sizeof(buf)) == -1)
            handle_errors("write error.\n");
        
        if (close(connfd) == -1)
            handle_errors("close error.\n");
    }
    exit(EXIT_SUCCESS);
}
