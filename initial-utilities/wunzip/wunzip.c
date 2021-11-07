#include <stdio.h>
#include <stdlib.h>

void decode(char ch, int size) {
  for (int i = 0; i < size; i++) {
    putchar(ch);
  }
}

int main(const int argc, const char** argv) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    const char* filename = argv[i];

    FILE* f = fopen(filename, "r");
    if (f == NULL) {
      exit(1);
    }

    int size;
    char ch;
    while (1) {
      fread(&size, sizeof(int), 1, f);
      if (feof(f)) break;
      fread(&ch, sizeof(char), 1, f);
      if (feof(f)) break;
      decode(ch, size);
    }

    fclose(f);
  }

  return 0;
}
