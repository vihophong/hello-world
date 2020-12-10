#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>


int sendsignal(char* ip,int port,int mess1, int mess2)
{
    struct UE
    {
            int mess1;
            int mess2;
    } ;
    UE UE1;
    UE1.mess1 = mess1;
    UE1.mess2 = mess2;
    int sock;
    struct sockaddr_in server;
    sock = socket(PF_INET, SOCK_STREAM , 0);
    //perror("Socket:");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    memset(&(server.sin_zero), '\0', 8);

    connect(sock, (struct sockaddr*)&server, sizeof(server));
    //perror("Connect:");

    send(sock, &UE1, sizeof(UE1), 0);
    //perror("send");
    //cout<<"Sent "<<UE1.mess1<<" and "<<UE1.mess2<<" to Server \n";
    close(sock);
}
int main()
{
    //! tcp/ip config
    int mess1 = 0;
    int mess2 = 50;
    int port = 10001;
    char* ip="192.168.6.106";
    struct UE
    {
            int mess1;
            int mess2;
    } ;
    UE UE1;
    UE1.mess1 = mess1;
    UE1.mess2 = mess2;
    int sock;
    struct sockaddr_in server;

    //read fifo
    int fd;
    char * myfifo = "/tmp/myfifo";
    //char buf[MAX_BUF];
    int buf;

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);

    while(1){
        ssize_t ncnt=read(fd, &buf, sizeof(buf));
        if (ncnt>0) {
            printf("Received: %d\n", buf);
            //if (buf>0) sendsignal("192.168.6.106",10001,0,50);
            if (buf>0) {
                sock = socket(PF_INET, SOCK_STREAM , 0);
                //perror("Socket:");
                server.sin_family = AF_INET;
                server.sin_port = htons(port);
                server.sin_addr.s_addr = inet_addr(ip);
                memset(&(server.sin_zero), '\0', 8);
                connect(sock, (struct sockaddr*)&server, sizeof(server));
                //perror("Connect:");
                send(sock, &UE1, sizeof(UE1), 0);
            }
            //perror("send");
        }
    }
    close(fd);
    close(sock);
    return 0;
}
