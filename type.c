
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char*argv[]) {

    if (argc < 3) {
        printf("Error: not enough arguments", stderr);
        return 1;
    }

    const int p_size = atoi(argv[1]);
    const int m_c_w = atoi(argv[2]);

    if (p_size == 0 && argv[1][0] != '0') {
        printf("Error: '%s' is not a valid integer\n", argv[1]), stderr;
        return 1;
    }

    if (m_c_w == 0 && argv[2][0] != '0') {
        printf("Error: '%s' is not a vaild integer\n", argv[2], stderr);
        return 1;
    }

    const int para_size = atoi(argv[1]);
    const int most_complex_word = atoi(argv[2]);

    srand((unsigned int)time(NULL));

    const char* filename = "words.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: unable to load file", stderr);
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
        // paragraph[a] = words[rd_num];
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
        scanf("%15s", test[a]);
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

    printf("Words per Minute:%d,\nAccuracy:%d\n", wpm, accuracy);


    return 0;
}
