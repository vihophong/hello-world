#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

using namespace std;

int blinkbeep(int pinno,int blinktime)
{
        wiringPiSetup();                        // Setup the library
        pinMode(pinno, OUTPUT);         // Configure GPIO0 as an output
        digitalWrite(pinno, LOW);
        digitalWrite(pinno, HIGH);
        delay(blinktime);
        digitalWrite(pinno, LOW);
        return 0;
}


int main()
{
        struct UE
        {
                int Net;
                int imsi;
        } ;
        UE UE2;

        int sock, cli, receive;
        struct sockaddr_in server, client;
        unsigned int len;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        perror("Socket:");

        server.sin_family = AF_INET;
        server.sin_port = htons(10001);
        server.sin_addr.s_addr = INADDR_ANY;
        memset(&(server.sin_zero), '\0', 8);

        len = sizeof(server);
        bind(sock, (struct sockaddr *)&server, len);
        perror("Bind:");

        listen(sock, 1);
        perror("Listen:");
	while(1){
		cli = accept(sock,(struct sockaddr *)&client, &len);
		perror("accept");
		receive = recv(cli, ( void*)&UE2, sizeof(UE2), 0);
		perror("recv");

		cout << "rec = "<<receive<<endl;
		if (UE2.imsi==16) blinkbeep(0,50);
	}
        close(sock);
        perror("close");
	return 0;
}
