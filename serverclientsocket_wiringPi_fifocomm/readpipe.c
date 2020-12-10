#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    //char buf[MAX_BUF];
    int buf;

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    while(1){
        ssize_t ncnt=read(fd, &buf, sizeof(buf));
        if (ncnt>0) printf("Received: %d\n", buf);
    }
    close(fd);

    return 0;
}
