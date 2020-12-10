#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    int buf=0;
    while(1){
        fd = open(myfifo, O_WRONLY|O_NONBLOCK);
        write(fd, &buf, sizeof(buf));
        printf("Send = %d\n",buf);
        usleep(1000000);
        buf++;
    }
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}
