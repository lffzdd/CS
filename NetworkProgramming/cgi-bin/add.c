#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 8192


void Respond(char* sumStr);
int main() {
    char* buf;


    if ((buf = getenv("QUERY_STRING")) != NULL) {
        char argv[100][100]; // 存放参数
        char* start = buf;
        char* p;
        int i = 1;
        while ((p = strchr(buf, '&')) != NULL) {
            *p = '\0';
            strcpy(argv[i], buf);
            i++;
            buf = p + 1;
        }
        strcpy(argv[i], buf);

        char sumStr[1024] = "";
        int sum = 0;
        for (int j = 1; j <= i; j++) {
            sprintf(sumStr + strlen(sumStr), "%d + ", atoi(argv[j]));
            sum += atoi(argv[j]);
        }
        sumStr[strlen(sumStr) - 2] = '='; // 去掉最后的加号,改为等号
        sprintf(sumStr + strlen(sumStr), "%d", sum);

        Respond(sumStr);
    }

    return 0;
}


void Respond(char* sumStr) {
    char header[MAXLINE] = "";
    sprintf(header + strlen(header), "Content-length: %d\r\n", (int)strlen(sumStr));

    char body[MAXLINE];
    sprintf(body, "<html><title>Welcome to add.com</title>");
    sprintf(body + strlen(body), "<body bgcolor=\"ffffff\">\r\n");
    sprintf(body + strlen(body), "<h1>答案是:</h1>\r\n");
    sprintf(body + strlen(body), "%s\r\n", sumStr);
    sprintf(body + strlen(body), "<br>感谢使用!\r\n</body></html>\r\n");

    printf("Content-type: text/html; charset=utf-8\r\n");
    printf("%s\r\n", header);
    printf("%s", body);
    fflush(stdout); // 刷新输出缓冲区
}