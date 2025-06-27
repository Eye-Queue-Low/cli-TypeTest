#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void read_words(const char* filename, char words[][15], int* word_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: unable to load file\n");
        exit(1);
    }

    *word_count = 0;
    while (fgets(words[*word_count], sizeof(words[0]), file) != NULL) {
        words[*word_count][strcspn(words[*word_count], "\n")] = '\0'; // Remove newline
        (*word_count)++;
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: not enough arguments\n");
        return 1;
    }

    char* endptr;
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

    char words[1000][15];
    int word_count = 0;
    read_words("words.txt", words, &word_count);

    // Generate paragraph
    char paragraph[p_size][15];
    for (int a = 0; a < p_size; a++) {
        int rd_num = rand() % word_count; // Use word_count instead of m_c_w
        strcpy(paragraph[a], words[rd_num]);
    }

    // Output paragraph
    for (int a = 0; a < p_size; a++) {
        printf("%s ", paragraph[a]);
    }
    printf("\n");

    // Get input
    time_t start_time, end_time;
    start_time = time(NULL);

    char test[p_size][15];
    for (int a = 0; a < p_size; a++) {
        scanf("%14s", test[a]); // Limit input to 14 characters
    }


