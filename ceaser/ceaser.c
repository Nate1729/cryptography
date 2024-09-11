#include "ceaser.h"

int is_uppercase(char c) {
  return ('A' <= c) && (c <= 'Z');
}

int is_lowercase(char c) {
  return ('a' <= c) && (c <='z');
}

char _encrypt_uppercase(unsigned key, char c) {
   return (((c-'A') + key) % 26) + 'A';
}

char _encrypt_lowercase(unsigned key, char c) { 
   return (((c-'a') + key) % 26) + 'a';
}

char encrypt(unsigned key, char c) {
  if (is_uppercase(c)) {
    return _encrypt_uppercase(key, c);
  }

  if (is_lowercase(c)) {
    return _encrypt_lowercase(key, c);
  }

  return c;
}
