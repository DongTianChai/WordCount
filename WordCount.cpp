#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
// ��������
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

// ͳ���ַ���
void countCharacters(FILE *file) {
    int ch;
    int count = 0;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    printf("�ַ�����%d\n", count);
}

// ͳ�Ƶ�����
void countWords(FILE *file) {
    int ch;
    int count = 0;
    int inWord = 0; // ����Ƿ��ڵ�����
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == '#') { // ������'#'��Ϊ���ʷָ����Ŀ�����
            if (!inWord) {
                inWord = 1;
                count++;
            }
        } else if (inWord) {
            inWord = 0;
        }
    }
    printf("��������%d\n", count);
}

// ���������������ַ����еĵ�������
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
