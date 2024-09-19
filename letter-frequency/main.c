#include <stdio.h>
#include <stdlib.h>

float *freq(unsigned *counts, unsigned length) {
  float total = 0, *freq;
  unsigned i;

  for (i=0; i<length; i++) {
    total += (float)counts[i];
  }

  freq = malloc(sizeof(float)*length); 
  if (freq == NULL) {
    fprintf(stderr, "Couldn't create memory.\n");
    return NULL;
  }

  for (i=0; i<length; i++) {
    freq[i] = (float)counts[i] / total;
  }

  return freq;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "No file was provided.\n");
    return 1;
  } else if (argc > 2) {
    fprintf(stderr, "Too many inputs, unsure which is file to process.\n");
    return 1;
  }

  FILE *f;
  char c;
  unsigned counts[26] = {0}, i;
  float *freqs;

  f = fopen(argv[1], "r");
  if (!f) {
    perror("Couldn't open file: ");
    return 1;
  }

  c = fgetc(f);
  while (c != EOF) {
    if (c >= 'a' && c <= 'z') {
      counts[c - 'a']++;
    }

    c = fgetc(f);
  }
  fclose(f);
  
  freqs = freq(counts, 26); 
  if (freqs == NULL) {
    return 1;
  }

  printf("Letter | Frequency\n");
  for (i=0; i<26; i++) {
    printf("%c\t\t %.3f\n", (char)i+'a', freqs[i]);
  }
  
  return 0;
}
