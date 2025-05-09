/**
 * C语言词法分析器
 * 支持识别C语言中的关键字、标识符、常量、运算符和界符
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

 // 词法单元的类型
typedef enum {
    // 关键字
    TOKEN_AUTO, TOKEN_BREAK, TOKEN_CASE, TOKEN_CHAR, TOKEN_CONST, TOKEN_CONTINUE,
    TOKEN_DEFAULT, TOKEN_DO, TOKEN_DOUBLE, TOKEN_ELSE, TOKEN_ENUM, TOKEN_EXTERN,
    TOKEN_FLOAT, TOKEN_FOR, TOKEN_GOTO, TOKEN_IF, TOKEN_INT, TOKEN_LONG,
    TOKEN_REGISTER, TOKEN_RETURN, TOKEN_SHORT, TOKEN_SIGNED, TOKEN_SIZEOF, TOKEN_STATIC,
    TOKEN_STRUCT, TOKEN_SWITCH, TOKEN_TYPEDEF, TOKEN_UNION, TOKEN_UNSIGNED, TOKEN_VOID,
    TOKEN_VOLATILE, TOKEN_WHILE,

    // 标识符和常量
    TOKEN_IDENTIFIER, TOKEN_INTEGER, TOKEN_FLOAT_NUM, TOKEN_CHAR_CONST, TOKEN_STRING_LITERAL,

    // 运算符
    TOKEN_ADD, TOKEN_SUB, TOKEN_MUL, TOKEN_DIV, TOKEN_MOD,
    TOKEN_INC, TOKEN_DEC, TOKEN_EQ, TOKEN_NEQ, TOKEN_LT, TOKEN_GT, TOKEN_LE, TOKEN_GE,
    TOKEN_AND, TOKEN_OR, TOKEN_NOT, TOKEN_BIT_AND, TOKEN_BIT_OR, TOKEN_BIT_XOR, TOKEN_BIT_NOT,
    TOKEN_SHL, TOKEN_SHR, TOKEN_ASSIGN, TOKEN_ADD_ASSIGN, TOKEN_SUB_ASSIGN, TOKEN_MUL_ASSIGN,
    TOKEN_DIV_ASSIGN, TOKEN_MOD_ASSIGN, TOKEN_AND_ASSIGN, TOKEN_OR_ASSIGN, TOKEN_XOR_ASSIGN,
    TOKEN_SHL_ASSIGN, TOKEN_SHR_ASSIGN,

    // 界符
    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LBRACKET, TOKEN_RBRACKET, TOKEN_LBRACE, TOKEN_RBRACE,
    TOKEN_SEMICOLON, TOKEN_COMMA, TOKEN_PERIOD, TOKEN_ARROW, TOKEN_COLON, TOKEN_QUESTION,

    // 特殊标记
    TOKEN_EOF, TOKEN_ERROR
} TokenType;

// 词法单元结构体
typedef struct {
    TokenType type;
    char* lexeme;
    int line;
    int column;
} Token;

// 全局变量
static char* source = NULL;
static char* current = NULL;
static int line = 1;
static int column = 1;

// 保存当前词素的缓冲区
static char lexeme_buffer[1024];
static int lexeme_len = 0;

// 关键字表
static struct {
    const char* keyword;
    TokenType type;
} keywords[] = {
    {"auto", TOKEN_AUTO},
    {"break", TOKEN_BREAK},
    {"case", TOKEN_CASE},
    {"char", TOKEN_CHAR},
    {"const", TOKEN_CONST},
    {"continue", TOKEN_CONTINUE},
    {"default", TOKEN_DEFAULT},
    {"do", TOKEN_DO},
    {"double", TOKEN_DOUBLE},
    {"else", TOKEN_ELSE},
    {"enum", TOKEN_ENUM},
    {"extern", TOKEN_EXTERN},
    {"float", TOKEN_FLOAT},
    {"for", TOKEN_FOR},
    {"goto", TOKEN_GOTO},
    {"if", TOKEN_IF},
    {"int", TOKEN_INT},
    {"long", TOKEN_LONG},
    {"register", TOKEN_REGISTER},
    {"return", TOKEN_RETURN},
    {"short", TOKEN_SHORT},
    {"signed", TOKEN_SIGNED},
    {"sizeof", TOKEN_SIZEOF},
    {"static", TOKEN_STATIC},
    {"struct", TOKEN_STRUCT},
    {"switch", TOKEN_SWITCH},
    {"typedef", TOKEN_TYPEDEF},
    {"union", TOKEN_UNION},
    {"unsigned", TOKEN_UNSIGNED},
    {"void", TOKEN_VOID},
    {"volatile", TOKEN_VOLATILE},
    {"while", TOKEN_WHILE},
    {NULL, 0}  // 结束标记
};

// 错误处理
void error(const char* message) {
    fprintf(stderr, "错误 (行 %d, 列 %d): %s\n", line, column, message);
}

// 初始化词法分析器
void init_lexer(const char* src) {
    source = strdup(src);
    current = source;
    line = 1;
    column = 1;
    lexeme_len = 0;
}

// 清理词法分析器
void free_lexer() {
    free(source);
    source = NULL;
    current = NULL;
}

// 向前查看一个字符但不前进
char peek() {
    return *current;
}

// 向前查看第二个字符但不前进
char peek_next() {
    if (*current == '\0') return '\0';
    return *(current + 1);
}

// 移动到下一个字符
char advance() {
    char c = *current++;
    if (c == '\n') {
        line++;
        column = 1;
    }
    else {
        column++;
    }
    return c;
}

// 向前移动如果当前字符匹配
bool match(char expected) {
    if (peek() != expected) return false;
    advance();
    return true;
}

// 添加字符到词素缓冲区
void add_to_lexeme(char c) {
    if (lexeme_len < sizeof(lexeme_buffer) - 1) {
        lexeme_buffer[lexeme_len++] = c;
        lexeme_buffer[lexeme_len] = '\0';
    }
    else {
        error("词素过长");
    }
}

// 创建一个新的词法单元
Token* make_token(TokenType type) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme_buffer);
    token->line = line;
    token->column = column - lexeme_len;
    lexeme_len = 0;  // 清空词素缓冲区
    return token;
}

// 创建一个错误词法单元
Token* error_token(const char* message) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = TOKEN_ERROR;
    token->lexeme = strdup(message);
    token->line = line;
    token->column = column;
    return token;
}

// 跳过空白字符和注释
void skip_whitespace_and_comments() {
    for (;;) {
        char c = peek();

        // 处理空白字符
        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
        }
        else if (c == '\n') {
            advance();
        }
        // 处理注释
        else if (c == '/' && peek_next() == '/') {
            // 单行注释
            while (peek() != '\n' && peek() != '\0')
                advance();
        }
        else if (c == '/' && peek_next() == '*') {
            // 多行注释
            advance(); // 跳过 '/'
            advance(); // 跳过 '*'

            while (!(peek() == '*' && peek_next() == '/')) {
                if (peek() == '\0') {
                    error("未闭合的多行注释");
                    return;
                }
                advance();
            }

            advance(); // 跳过 '*'
            advance(); // 跳过 '/'
        }
        else {
            return;
        }
    }
}

// 检查是否是关键字
TokenType check_keyword() {
    for (int i = 0; keywords[i].keyword != NULL; i++) {
        if (strcmp(lexeme_buffer, keywords[i].keyword) == 0) {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENTIFIER;
}

// 处理标识符
Token* identifier() {
    while (isalnum(peek()) || peek() == '_')
        add_to_lexeme(advance());

    return make_token(check_keyword());
}

// 处理数字
Token* number() {
    TokenType type = TOKEN_INTEGER;

    // 处理整数部分
    while (isdigit(peek()))
        add_to_lexeme(advance());

    // 处理小数部分
    if (peek() == '.' && isdigit(peek_next())) {
        type = TOKEN_FLOAT_NUM;
        add_to_lexeme(advance()); // 添加小数点

        while (isdigit(peek()))
            add_to_lexeme(advance());
    }

    // 处理科学计数法 (e.g., 1.23e45)
    if ((peek() == 'e' || peek() == 'E')) {
        type = TOKEN_FLOAT_NUM;
        add_to_lexeme(advance()); // 添加 'e' 或 'E'

        // 处理可能的符号
        if (peek() == '+' || peek() == '-')
            add_to_lexeme(advance());

        if (!isdigit(peek())) {
            return error_token("科学计数法格式不正确");
        }

        while (isdigit(peek()))
            add_to_lexeme(advance());
    }

    // 处理后缀 (e.g., 123L, 1.23f)
    if (peek() == 'f' || peek() == 'F' || peek() == 'l' || peek() == 'L')
        add_to_lexeme(advance());

    return make_token(type);
}

// 处理字符常量
Token* char_constant() {
    advance(); // 跳过起始的单引号

    char c = peek();
    if (c == '\0' || c == '\n') {
        return error_token("未闭合的字符常量");
    }
    else if (c == '\'') {
        advance(); // 跳过右引号
        return error_token("空的字符常量");
    }

    // 处理转义字符
    if (c == '\\') {
        add_to_lexeme(advance()); // 添加反斜杠
        c = peek();
        if (c == 'n' || c == 't' || c == 'r' || c == '0' || c == '\'' || c == '\"' || c == '\\') {
            add_to_lexeme(advance());
        }
        else {
            return error_token("无效的转义序列");
        }
    }
    else {
        add_to_lexeme(advance());
    }

    if (peek() != '\'') {
        return error_token("字符常量不能包含多个字符");
    }

    advance(); // 跳过结束的单引号
    return make_token(TOKEN_CHAR_CONST);
}

// 处理字符串字面量
Token* string() {
    advance(); // 跳过起始的双引号

    while (peek() != '\"' && peek() != '\0') {
        if (peek() == '\n') {
            return error_token("字符串字面量中不能包含换行符");
        }

        if (peek() == '\\') {
            add_to_lexeme(advance());
        }

        add_to_lexeme(advance());
    }

    if (peek() == '\0') {
        return error_token("未闭合的字符串");
    }

    advance(); // 跳过结束的双引号
    return make_token(TOKEN_STRING_LITERAL);
}

// 打印词法单元
void print_token(Token* token) {
    const char* type_str;

    switch (token->type) {
        // 输出每种词法单元的名称
        case TOKEN_AUTO: type_str = "KEYWORD_AUTO"; break;
        case TOKEN_BREAK: type_str = "KEYWORD_BREAK"; break;
        case TOKEN_CASE: type_str = "KEYWORD_CASE"; break;
        case TOKEN_CHAR: type_str = "KEYWORD_CHAR"; break;
        case TOKEN_CONST: type_str = "KEYWORD_CONST"; break;
        case TOKEN_CONTINUE: type_str = "KEYWORD_CONTINUE"; break;
        case TOKEN_DEFAULT: type_str = "KEYWORD_DEFAULT"; break;
        case TOKEN_DO: type_str = "KEYWORD_DO"; break;
        case TOKEN_DOUBLE: type_str = "KEYWORD_DOUBLE"; break;
        case TOKEN_ELSE: type_str = "KEYWORD_ELSE"; break;
        case TOKEN_ENUM: type_str = "KEYWORD_ENUM"; break;
        case TOKEN_EXTERN: type_str = "KEYWORD_EXTERN"; break;
        case TOKEN_FLOAT: type_str = "KEYWORD_FLOAT"; break;
        case TOKEN_FOR: type_str = "KEYWORD_FOR"; break;
        case TOKEN_GOTO: type_str = "KEYWORD_GOTO"; break;
        case TOKEN_IF: type_str = "KEYWORD_IF"; break;
        case TOKEN_INT: type_str = "KEYWORD_INT"; break;
        case TOKEN_LONG: type_str = "KEYWORD_LONG"; break;
        case TOKEN_REGISTER: type_str = "KEYWORD_REGISTER"; break;
        case TOKEN_RETURN: type_str = "KEYWORD_RETURN"; break;
        case TOKEN_SHORT: type_str = "KEYWORD_SHORT"; break;
        case TOKEN_SIGNED: type_str = "KEYWORD_SIGNED"; break;
        case TOKEN_SIZEOF: type_str = "KEYWORD_SIZEOF"; break;
        case TOKEN_STATIC: type_str = "KEYWORD_STATIC"; break;
        case TOKEN_STRUCT: type_str = "KEYWORD_STRUCT"; break;
        case TOKEN_SWITCH: type_str = "KEYWORD_SWITCH"; break;
        case TOKEN_TYPEDEF: type_str = "KEYWORD_TYPEDEF"; break;
        case TOKEN_UNION: type_str = "KEYWORD_UNION"; break;
        case TOKEN_UNSIGNED: type_str = "KEYWORD_UNSIGNED"; break;
        case TOKEN_VOID: type_str = "KEYWORD_VOID"; break;
        case TOKEN_VOLATILE: type_str = "KEYWORD_VOLATILE"; break;
        case TOKEN_WHILE: type_str = "KEYWORD_WHILE"; break;

        case TOKEN_IDENTIFIER: type_str = "IDENTIFIER"; break;
        case TOKEN_INTEGER: type_str = "INTEGER"; break;
        case TOKEN_FLOAT_NUM: type_str = "FLOAT"; break;
        case TOKEN_CHAR_CONST: type_str = "CHAR"; break;
        case TOKEN_STRING_LITERAL: type_str = "STRING"; break;

        case TOKEN_ADD: type_str = "ADD"; break;
        case TOKEN_SUB: type_str = "SUB"; break;
        case TOKEN_MUL: type_str = "MUL"; break;
        case TOKEN_DIV: type_str = "DIV"; break;
        case TOKEN_MOD: type_str = "MOD"; break;
        case TOKEN_INC: type_str = "INC"; break;
        case TOKEN_DEC: type_str = "DEC"; break;
        case TOKEN_EQ: type_str = "EQ"; break;
        case TOKEN_NEQ: type_str = "NEQ"; break;
        case TOKEN_LT: type_str = "LT"; break;
        case TOKEN_GT: type_str = "GT"; break;
        case TOKEN_LE: type_str = "LE"; break;
        case TOKEN_GE: type_str = "GE"; break;
        case TOKEN_AND: type_str = "AND"; break;
        case TOKEN_OR: type_str = "OR"; break;
        case TOKEN_NOT: type_str = "NOT"; break;
        case TOKEN_BIT_AND: type_str = "BIT_AND"; break;
        case TOKEN_BIT_OR: type_str = "BIT_OR"; break;
        case TOKEN_BIT_XOR: type_str = "BIT_XOR"; break;
        case TOKEN_BIT_NOT: type_str = "BIT_NOT"; break;
        case TOKEN_SHL: type_str = "SHL"; break;
        case TOKEN_SHR: type_str = "SHR"; break;
        case TOKEN_ASSIGN: type_str = "ASSIGN"; break;
        case TOKEN_ADD_ASSIGN: type_str = "ADD_ASSIGN"; break;
        case TOKEN_SUB_ASSIGN: type_str = "SUB_ASSIGN"; break;
        case TOKEN_MUL_ASSIGN: type_str = "MUL_ASSIGN"; break;
        case TOKEN_DIV_ASSIGN: type_str = "DIV_ASSIGN"; break;
        case TOKEN_MOD_ASSIGN: type_str = "MOD_ASSIGN"; break;
        case TOKEN_AND_ASSIGN: type_str = "AND_ASSIGN"; break;
        case TOKEN_OR_ASSIGN: type_str = "OR_ASSIGN"; break;
        case TOKEN_XOR_ASSIGN: type_str = "XOR_ASSIGN"; break;
        case TOKEN_SHL_ASSIGN: type_str = "SHL_ASSIGN"; break;
        case TOKEN_SHR_ASSIGN: type_str = "SHR_ASSIGN"; break;

        case TOKEN_LPAREN: type_str = "LPAREN"; break;
        case TOKEN_RPAREN: type_str = "RPAREN"; break;
        case TOKEN_LBRACKET: type_str = "LBRACKET"; break;
        case TOKEN_RBRACKET: type_str = "RBRACKET"; break;
        case TOKEN_LBRACE: type_str = "LBRACE"; break;
        case TOKEN_RBRACE: type_str = "RBRACE"; break;
        case TOKEN_SEMICOLON: type_str = "SEMICOLON"; break;
        case TOKEN_COMMA: type_str = "COMMA"; break;
        case TOKEN_PERIOD: type_str = "PERIOD"; break;
        case TOKEN_ARROW: type_str = "ARROW"; break;
        case TOKEN_COLON: type_str = "COLON"; break;
        case TOKEN_QUESTION: type_str = "QUESTION"; break;

        case TOKEN_EOF: type_str = "EOF"; break;
        case TOKEN_ERROR: type_str = "ERROR"; break;
        default: type_str = "UNKNOWN"; break;
    }

    printf("%-15s '%s' (行 %d, 列 %d)\n", type_str, token->lexeme, token->line, token->column);
}

// 释放词法单元
void free_token(Token* token) {
    free(token->lexeme);
    free(token);
}

// 获取下一个词法单元
Token* scan_token() {
    skip_whitespace_and_comments();

    if (*current == '\0')
        return make_token(TOKEN_EOF);

    char c = peek();

    // 标识符
    if (isalpha(c) || c == '_')
        return identifier();

    // 数字
    if (isdigit(c))
        return number();

    // 单字符词法单元和复合词法单元
    switch (c) {
        case '(': add_to_lexeme(advance()); return make_token(TOKEN_LPAREN);
        case ')': add_to_lexeme(advance()); return make_token(TOKEN_RPAREN);
        case '[': add_to_lexeme(advance()); return make_token(TOKEN_LBRACKET);
        case ']': add_to_lexeme(advance()); return make_token(TOKEN_RBRACKET);
        case '{': add_to_lexeme(advance()); return make_token(TOKEN_LBRACE);
        case '}': add_to_lexeme(advance()); return make_token(TOKEN_RBRACE);
        case ';': add_to_lexeme(advance()); return make_token(TOKEN_SEMICOLON);
        case ',': add_to_lexeme(advance()); return make_token(TOKEN_COMMA);
        case '.': add_to_lexeme(advance()); return make_token(TOKEN_PERIOD);
        case ':': add_to_lexeme(advance()); return make_token(TOKEN_COLON);
        case '?': add_to_lexeme(advance()); return make_token(TOKEN_QUESTION);

        case '+':
            add_to_lexeme(advance());
            if (peek() == '+') { add_to_lexeme(advance()); return make_token(TOKEN_INC); }
            else if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_ADD_ASSIGN); }
            return make_token(TOKEN_ADD);

        case '-':
            add_to_lexeme(advance());
            if (peek() == '-') { add_to_lexeme(advance()); return make_token(TOKEN_DEC); }
            else if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_SUB_ASSIGN); }
            else if (peek() == '>') { add_to_lexeme(advance()); return make_token(TOKEN_ARROW); }
            return make_token(TOKEN_SUB);

        case '*':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_MUL_ASSIGN); }
            return make_token(TOKEN_MUL);

        case '/':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_DIV_ASSIGN); }
            return make_token(TOKEN_DIV);

        case '%':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_MOD_ASSIGN); }
            return make_token(TOKEN_MOD);

        case '=':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_EQ); }
            return make_token(TOKEN_ASSIGN);

        case '!':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_NEQ); }
            return make_token(TOKEN_NOT);

        case '<':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_LE); }
            else if (peek() == '<') {
                add_to_lexeme(advance());
                if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_SHL_ASSIGN); }
                return make_token(TOKEN_SHL);
            }
            return make_token(TOKEN_LT);

        case '>':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_GE); }
            else if (peek() == '>') {
                add_to_lexeme(advance());
                if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_SHR_ASSIGN); }
                return make_token(TOKEN_SHR);
            }
            return make_token(TOKEN_GT);

        case '&':
            add_to_lexeme(advance());
            if (peek() == '&') { add_to_lexeme(advance()); return make_token(TOKEN_AND); }
            else if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_AND_ASSIGN); }
            return make_token(TOKEN_BIT_AND);

        case '|':
            add_to_lexeme(advance());
            if (peek() == '|') { add_to_lexeme(advance()); return make_token(TOKEN_OR); }
            else if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_OR_ASSIGN); }
            return make_token(TOKEN_BIT_OR);

        case '^':
            add_to_lexeme(advance());
            if (peek() == '=') { add_to_lexeme(advance()); return make_token(TOKEN_XOR_ASSIGN); }
            return make_token(TOKEN_BIT_XOR);

        case '~':
            add_to_lexeme(advance());
            return make_token(TOKEN_BIT_NOT);

        case '\'': return char_constant();
        case '"': return string();
    }

    // 无法识别的字符
    char err_msg[64];
    snprintf(err_msg, sizeof(err_msg), "无法识别的字符: '%c'", c);
    return error_token(err_msg);
}

// 主函数示例
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("用法: %s <源文件>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("无法打开文件");
        return 1;
    }

    // 读取整个文件
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = (char*)malloc(size + 1);
    if (!source) {
        perror("内存分配失败");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(source, 1, size, file);
    source[bytes_read] = '\0';
    fclose(file);

    // 初始化词法分析器
    init_lexer(source);

    // 分析所有词法单元
    printf("词法分析结果:\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("类型            词素                行号    列号\n");
    printf("-------------------------------------------------------------------------------\n");

    Token* token;
    do {
        token = scan_token();
        print_token(token);
        free_token(token);
    } while (token->type != TOKEN_EOF && token->type != TOKEN_ERROR);

    // 清理
    free(source);
    free_lexer();

    return 0;
}