#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int match(const char* line, const char* pattern) {
  for (int i = 0; i + strlen(pattern) < strlen(line); i++) {
    if (strncmp(line + i, pattern, strlen(pattern)) == 0) {
      return 1;
    }
  }

  return 0;
}

void process(const char* line, const char* pattern) {
  if (match(line, pattern)) {
    printf("%s", line);
  }
}

int main(const int argc, const char** argv) {
  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  const char* pattern = argv[1];
  FILE *f;
  if (argc == 2) {
    f = stdin;
  } else {
    const char* filename = argv[2];

    f = fopen(filename, "r");
    if (f == NULL) {
      printf("wgrep: cannot open file\n");
      exit(1);
    }
  }

  char buf[32];
  int size = 0;
  char* line = calloc(size, sizeof(buf));
  while (fgets(buf, sizeof(buf), f) != NULL) {
    size++;
    line = realloc(line, size * sizeof(buf));

    int found = 0;
    for (int i = 0; i < sizeof(buf); i++) {
      if (buf[i] == '\n') {
        strncat(line, buf, i + 1);
        process(line, pattern);
        size = 1;
        line = calloc(size, sizeof(buf));
        strcpy(buf, buf + i + 1);
        break;
      }
    }

    strcat(line, buf);
  }

  fclose(f);

  return 0;
}
