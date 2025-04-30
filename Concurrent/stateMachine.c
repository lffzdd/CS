#include <stdio.h>

typedef enum {
    STATE_1 = 1,
    STATE_2,
    STATE_3,
    STATE_4
} State;

int main(int argc, char const* argv[]) {
    int input;
    State state = STATE_1;

    // 如果没有输入或者输入文件名不合法
    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    FILE* output = fopen("outputs.txt", "w");
    if (output == NULL) {
        printf("Error opening output file.\n");
        fclose(file);
        return 1;
    }

    // 读取文件内容
    while ((input = fgetc(file)) != EOF) {
        switch (state) {
            case STATE_1:
                if (input == '1') {
                    fputc('0', output);
                    state = STATE_2;
                } else {
                    fputc('0', output);
                    state = STATE_1;
                }
                break;
            case STATE_2:
                if (input == '0') {
                    fputc('0', output);
                    state = STATE_3;
                } else {
                    fputc('0', output);
                    state = STATE_2;
                }
                break;
            case STATE_3:
                if (input == '1') {
                    fputc('0', output);
                    state = STATE_4;
                } else {
                    fputc('0', output);
                    state = STATE_1;
                }
                break;
            case STATE_4:
                if (input == '1') {
                    fputc('1', output);
                    state = STATE_2;
                } else {
                    fputc('0', output);
                    state = STATE_3;
                }
                break;
            default:
                fputc('0', output);  // 处理未定义状态
                state = STATE_1;      // 重置状态
                break;
        }
    }

    fclose(file);
    fclose(output);
    printf("Processing complete. Output written to outputs.txt\n");
    return 0;
}
