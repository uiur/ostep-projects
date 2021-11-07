#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  for (int i = 1; i < argc; i++) {
    const char* filename = argv[i];
    char buf[8];
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }

    while (fgets(buf, sizeof(buf), f) != NULL) {
      printf("%s", buf);
    }
    fclose(f);
  }

  return 0;
}
