#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
// 函数声明
void countCharacters(FILE *file);
void countWords(FILE *file);
int countWord(const char *str, int start);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] input_file\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        countCharacters(file);
    } else if (strcmp(argv[1], "-w") == 0) {
        countWords(file);
    } else {
        printf("Invalid parameter. Use either '-c' or '-w'\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

// 统计字符数
void countCharacters(FILE *file) {
    int ch;
    int count = 0;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    printf("字符数：%d\n", count);
}

// 统计单词数
void countWords(FILE *file) {
    int ch;
    int count = 0;
    int inWord = 0; // 标记是否在单词内
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == '#') { // 考虑了'#'作为单词分隔符的可能性
            if (!inWord) {
                inWord = 1;
                count++;
            }
        } else if (inWord) {
            inWord = 0;
        }
    }
    printf("单词数：%d\n", count);
}

// 辅助函数：计算字符串中的单词数量
int countWord(const char *str, int start) {
    int count = 0;
    int inWord = 0;
    for (int i = start; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            if (!inWord) {
                inWord = 1;
                count++;
            }
        } else if (inWord) {
            inWord = 0;
        }
    }
    return count;
}
