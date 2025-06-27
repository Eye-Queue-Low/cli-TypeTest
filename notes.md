
# Project Notes

## How to read files

1. Header:
```
#include <stdio.h>
```

2. Pointer:
```
FILE* fptr;
```

3. Open:
```
fptr = fopen("filename.txt", "r");

if (fptr == NULL) {
    printf("Error: unable to open file", stderr);
    return 1;
}
```

4. Read:
- char:
```
char ch;
while ((ch = fgetc(fptf)) != EOF) {
    printf("%c", ch);
}
```

- string:
```
char buffer[100];
while (fgets(buffer, sizeof(buffer), fptf) != NULL) {
    printf("%s", buffer);
}
```

- scan:
```
int number;
char name[50];
while (fscanf(fptr, "%d, %s", &number, name) == 2) {
    printf("Number: %d, Name: %s\n", number, name);
}
```

- read:
```
struct MyData {
    int id;
    float value;
}

struct MyData data;
while (fread(&data, sizeof(struct MyData), 1, fptr) == 1) {
    printf("ID: %d, Value: %.2f\n", data,id, data.value);
}
```

5. Close:
```
fclose(fptr);
```
