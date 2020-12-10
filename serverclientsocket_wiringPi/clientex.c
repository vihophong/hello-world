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
using namespace std;
int main(int argc, char *argv[])
{
        struct UE
        {
                int Net;
                int imsi;
        } ;
        UE UE1;
        UE1.Net = atoi(argv[3]);
        UE1.imsi = atoi(argv[4]); 
        int sock, receive;
        struct sockaddr_in server;
        char mesg[200];
        sock = socket(PF_INET, SOCK_STREAM, 0);
        perror("Socket:");

        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[2]));
        server.sin_addr.s_addr = inet_addr(argv[1]);
        memset(&(server.sin_zero), '\0', 8);

        connect(sock, (struct sockaddr*)&server, sizeof(server));
        perror("Connect:");

        int count = 0;
        send(sock, &UE1, sizeof(UE1), 0);
        perror("send");
        cout<<"Sent "<<UE1.imsi<<" and "<<UE1.Net<<" to Server \n";
        close(sock);
}
