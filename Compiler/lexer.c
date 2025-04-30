#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

// C语言中的一些关键字
const char* keywords[] = {
    "int", "float", "return", "if", "else", "while", "for", "void", "char", "double", "break", "continue"
};
int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

// 检查一个字符串是否为关键字
int is_keyword(const char* str) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// 读取下一个字符，但不消耗它
int peek(FILE* fp) {
    int c = fgetc(fp);
    ungetc(c, fp); // 将字符放回文件流
    return c;
}

// 跳过空白字符和注释
void skip_whitespace_and_comments(FILE* fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            continue;
        }
        else if (c == '/') {
            int next = fgetc(fp);
            if (next == '/') {
                // 单行注释
                while ((c = fgetc(fp)) != '\n' && c != EOF);
            }
            else if (next == '*') {
                // 多行注释
                while (1) {
                    c = fgetc(fp);
                    if (c == EOF) break;
                    if (c == '*') {
                        if ((c = fgetc(fp)) == '/') break;
                        else ungetc(c, fp);
                    }
                }
            }
            else {
                ungetc(next, fp);
                ungetc(c, fp);
                break;
            }
        }
        else {
            ungetc(c, fp);
            break;
        }
    }
}

// 判断是否是分隔符
int is_delimiter(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' ||
        c == '{' || c == '}' || c == '[' || c == ']';
}

// 判断是否是运算符的起始字符
int is_operator_char(char c) {
    return strchr("+-*/%=!<>&|", c) != NULL;
}

// 处理标识符或关键字
void process_identifier(FILE* fp, int first_char) {
    char buffer[MAX_TOKEN_LEN];
    int i = 0;
    buffer[i++] = first_char;

    int c;
    while (isalnum(c = fgetc(fp)) || c == '_') { // isalnum() 允许字母和数字
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    ungetc(c, fp);

    if (is_keyword(buffer)) {
        printf("[KEYWORD]    %s\n", buffer);
    }
    else {
        printf("[IDENTIFIER] %s\n", buffer);
    }
}

// 处理数字（仅支持整数）
void process_number(FILE* fp, int first_char) {
    char buffer[MAX_TOKEN_LEN];
    int i = 0;
    buffer[i++] = first_char;

    int c;
    while (isdigit(c = fgetc(fp))) {
        buffer[i++] = c;
    }

    // 处理小数点和小数部分
    if (c == '.') {
        buffer[i++] = c; // 加入小数点
        while (isdigit(c = fgetc(fp))) {
            buffer[i++] = c;
        }
    }

    buffer[i] = '\0';
    ungetc(c, fp);

    printf("[NUMBER]     %s\n", buffer);
}

// 处理运算符（支持 ==, !=, >=, <=, &&, ||）
void process_operator(FILE* fp, int first_char) {
    int c = fgetc(fp);
    if ((first_char == '=' && c == '=') ||
        (first_char == '!' && c == '=') ||
        (first_char == '<' && c == '=') ||
        (first_char == '>' && c == '=') ||
        (first_char == '&' && c == '&') ||
        (first_char == '|' && c == '|')) {
        printf("[OPERATOR]   %c%c\n", first_char, c);
    }
    else {
        ungetc(c, fp);
        printf("[OPERATOR]   %c\n", first_char);
    }
}

// 处理分隔符
void process_delimiter(int c) {
    printf("[DELIMITER]  %c\n", c);
}

// 词法分析主函数
void lexer(FILE* fp) {
    int c;

    while ((c = fgetc(fp)) != EOF) {
        // 跳过空格/注释
        // ungetc(c, fp);
        skip_whitespace_and_comments(fp);

        // c = fgetc(fp);
        // if (c == EOF) break;

        if (isalpha(c) || c == '_') {
            process_identifier(fp, c);
        }
        else if (isdigit(c)) {
            process_number(fp, c);
        }
        else if (is_operator_char(c)) {
            process_operator(fp, c);
        }
        else if (is_delimiter(c)) {
            process_delimiter(c);
        }
        else {
            printf("[UNKNOWN]    %c\n", c);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("用法: %s <源文件.c>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("无法打开文件");
        return 1;
    }

    lexer(fp);
    fclose(fp);
    return 0;
}
