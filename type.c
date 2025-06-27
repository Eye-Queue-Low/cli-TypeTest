
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: not enough arguments\n");
        return 1;
    }

    char *endptr;
    const int p_size = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || p_size <= 0) {
        fprintf(stderr, "Error: '%s' is not a valid positive integer\n", argv[1]);
        return 1;
    }

    const int m_c_w = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || m_c_w <= 0) {
        fprintf(stderr, "Error: '%s' is not a valid positive integer\n", argv[2]);
        return 1;
    }

    srand((unsigned int)time(NULL));

    const char* filename = "words.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: unable to load file\n");
        return 1;
    }

    char words[1000][15];
    int i = 0;
    while (i < 1000 && fscanf(file, "%14s", words[i]) == 1) {
        i++;
    }
    fclose(file);

    // Check if we have enough words
    if (i < m_c_w) {
        fprintf(stderr, "Error: not enough words in the file\n");
        return 1;
    }

    // Making paragraph
    char paragraph[p_size][15];
    for (int a = 0; a < p_size; a++) {
        int rd_num = rand() % m_c_w;
        strcpy(paragraph[a], words[rd_num]);
    }

    // Output paragraph
    for (int a = 0; a < p_size; a++) {
        printf("%s ", paragraph[a]);
        if ((a + 1) % 25 == 0) {
            printf("\n");
        }
    }
    printf("\n-----------------------------------------------------------------------------------------\n");

    // Get input
    time_t start_time, end_time;
    double elapsed_time;

    start_time = time(NULL);
    char test[p_size][15];
    for (int a = 0; a < p_size; a++) {
        scanf("%14s", test[a]);
    }
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);

    // WPM
    int wpm = (p_size * 60) / elapsed_time;

    // Accuracy
    int words_correct = 0;
    for (int a = 0; a < p_size; a++) {
        if (strcmp(test[a], paragraph[a]) == 0) {
            words_correct++;
        }
    }
    int accuracy = (words_correct * 100) / p_size;

    printf("Words per Minute: %d,\nAccuracy: %d%%\n", wpm, accuracy);

    return 0;
}
