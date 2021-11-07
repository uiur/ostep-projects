#include <stdio.h>
#include <stdlib.h>

void put(char current, int size) {
  fwrite(&size, sizeof(int), 1, stdout);
  fwrite(&current, sizeof(char), 1, stdout);
}

int main(const int argc, const char** argv) {
  if (argc < 2) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  int ch;
  int size = 0;
  char current = '\0';

  for (int i = 1; i < argc; i++) {
    const char* filename = argv[i];
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
      exit(1);
    }

    while ((ch = fgetc(f)) != EOF) {
      if (current == '\0') current = ch;
      if (ch != current) {
        put(current, size);
        size = 0;
        current = ch;
      }
      size++;
    }

    fclose(f);
  }

  if (size > 0) {
    put(current, size);
  }


  return 0;
}
