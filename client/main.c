//
// Created by root on 16-10-31.
//

#include "serial.h"
#include <signal.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100
char buffer[MAX_BUFFER_SIZE];
char eventNum[20];
char valueNum[20];

int fd_serial = FALSE;
char serialName[20] = "/dev/ttyS0";

void quit(int signum){
    printf("catch signal SIGINT\n");
    UART_Close(fd_serial);
    printf("关闭 \"%s\"\n", serialName);
    exit(0);
}

char* getEventName() {
    static double p = 0.7;  // increase事件的概率
    if (rand() > RAND_MAX * p) return "decrease";
    else return "increase";

//    eventNum++;
//    if (rand() > RAND_MAX * (1 - p)) {
////        return rand() % 10 + 1;  // 返回一个异常的事件编号
//        return -1;
//    }
//    else return eventNum % 5 + 1;
}

int getValueNum() {
    return rand() % 60;

//    static int valueNum = -1;
//    static double p = 0.2;
//
//    valueNum++;
//    if (rand() > RAND_MAX * (1 - p)) {
//        return rand();  // 模拟事件篡改
//    }
//    else return valueNum % 100 + 1;
}

int main(int argc, char** argv){

    if (argc == 2) {
        strcpy(serialName, argv[1]);
    }
    else if (argc != 1) {
        printf("Usage: ./serialClient serialName\n");
        return 1;
    }

    int ret = FALSE;
    char buf[MAXSIZE];
    memset(buf, 0, sizeof(buf));

    //serial open and init
    fd_serial = UART_Open(fd_serial, serialName);
    if(FALSE == fd_serial){
        printf("open \"%s\" error\n", serialName);
        return 1;
    }
    else {
        printf("open \"%s\"\n", serialName);
    }
    ret = UART_Init(fd_serial,9600,0,8,1,'N');
    if (FALSE == ret){
        printf("Set Port \"%s\" Error\n", serialName);
        return 1;
    }
    else{
        printf("set port \"%s\" success\n", serialName);
    }

    signal(SIGINT, quit);

    //loop
    while(1){
        strcpy(buffer, "<event name=\"");
        char* eventName = getEventName();
        strcat(buffer, eventName);
        strcat(buffer, "\" value=\"x = ");
        sprintf(valueNum, "%d", getValueNum());
        strcat(buffer, valueNum);
        strcat(buffer, "\"/>");
//        if (eventNumInt < 0) continue;  // 模拟事件丢失

        if (UART_Send(fd_serial, buffer, strlen(buffer)) < 0) {
            printf("Send message %s failed!", buffer);
            break;
        }
        printf("%s\n", buffer);
        sleep(1);
    }

    return 0;
}

