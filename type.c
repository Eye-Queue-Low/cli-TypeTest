#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: not enough arguments\n");
        return 1;
    }

    char *endptr;
    long p_size = strtol(argv[1], &endptr, 10);
    long m_c_w = strtol(argv[2], &endptr, 10);

    if (*endptr != '\0' || p_size == LONG_MIN || p_size == LONG_MAX || m_c_w == LONG_MIN || m_c_w == LONG_MAX) {
        fprintf(stderr, "Error: '%s' and '%s' must be valid integers\n", argv[1], argv[2]);
        return 1;
    }

    if (p_size <= 0 || m_c_w <= 0) {
        fprintf(stderr, "Error: both arguments must be positive integers\n");
        return 1;
    }

    const int para_size = (int)p_size;
    const int most_complex_word = (int)m_c_w;

    srand((unsigned int)time(NULL));

    const char *filename = "words.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: unable to load file\n");
        return 1;
    }

    char words[1000][15];
    int i = 0;
    int j = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            words[i][j] = '\0';
            i++;
            j = 0;
        } else {
            words[i][j] = ch;
            j++;
        }
    }
    fclose(file);

    // making paragraph
    char paragraph[para_size][15];
    for (int a = 0; a < para_size; a++) {
        int rd_num = rand() % most_complex_word;
        strcpy(paragraph[a], words[rd_num]);
    }

    // output paragraph
    for (int a = 0; a < para_size; a++) {
        printf("%s ", paragraph[a]);
    }
    printf("\n");

    // get input
    time_t start_time, end_time;
    double elapsed_time;

    start_time = time(NULL);

    char test[para_size][15];
    for (int a = 0; a < para_size; a++) {
        scanf("%14s", test[a]);
    }

    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);

    // wpm
    int wpm = (para_size * 60) / elapsed_time;

    // accuracy
    int words_correct = 0;
    for (int a = 0; a < para_size; a++) {
        if (strcmp(test[a], paragraph[a]) == 0) {
            words_correct += 1;
        }
    }
    int accuracy = (words_correct * 100) / para_size;

    printf("Words per Minute: %d\nAccuracy: %d%%\n", wpm, accuracy);

    return 0;
}
