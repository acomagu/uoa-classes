#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Caesar Decryption */
char *CaesarDecrypt(int, char *);
/* BruteForceAttack */
void BruteForceAttack(char *, char *);

int mod(int, int);
void chomp(char *);

int main() {
  char ciphertext[1024];
  char keyword[1024];

  /*
    Input ciphertext and keyword.
    If keyword is not specified (no keyword), press ENTER
  */
  printf("Input ciphertext: ");
  if (fgets(ciphertext, 1024, stdin) == NULL)
    return 1;
  chomp(ciphertext);

  printf("Input keyword: ");
  if (fgets(keyword, 1024, stdin) == NULL)
    return 1;
  chomp(keyword);

  BruteForceAttack(ciphertext, keyword);
  return 0;
}

void BruteForceAttack(char *ciphertext, char *keyword) {
  int printAny = 0;
  int key;
  for (key = 0; key < 26; key++) {
    char *plaintext = CaesarDecrypt(key, ciphertext);
    if (strstr(plaintext, keyword) != NULL) {
      printAny = 1;
      printf("Key: %2d Plaintext: %s\n", key, plaintext);
    }
  }
  if (!printAny)
    printf("There is no decryption for keyword: %s\n", keyword);
}

char *CaesarDecrypt(int key, char *ciphertext) {
  char *ret = (char *)malloc(sizeof(char) * 1024);
  int i;
  for (i = 0; i < 1024; i++) {
    ret[i] = ciphertext[i];
    if (ciphertext[i] == 0)
      break;
    if (ciphertext[i] < 65)
      continue;
    else if (ciphertext[i] <= 90)
      ret[i] = mod(ret[i] - 65 - key, 26) + 65;
    else if (ciphertext[i] < 97)
      continue;
    else if (ciphertext[i] <= 122)
      ret[i] = mod(ret[i] - 97 - key, 26) + 97;
  }
  return ret;
}

int mod(int a, int b) {
  int m = a % b;
  return m >= 0 ? m : b + m;
}

void chomp(char *text) {
  char *c;
  for (c = text; *c != 0; c++) {
    if (*c == '\n') {
      *c = 0;
      break;
    }
  }
}
