#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Caesar Encryption
char *CaesarEncrypt(int, char *);
// Caesar Decryption
char *CaesarDecrypt(int, char *);

int mod(int, int);

int main(void) {
  char plaintext[1024];
  char *ciphertext;
  char *decrypttext;

  int key;
  char key_s[1024];

  // Input plaintext and key.
  // Check the validity of key(key must be an integer number between 0 ~ 25).
  printf("Input plainText: ");
  if (fgets(plaintext, 1024, stdin) == NULL)
    return 1;
  strtok(plaintext, "\n"); // Chomp.

  printf("Input key(an integer from 1 to 25): ");
  if (fgets(key_s, 1024, stdin) == NULL)
    return 1;

  char *end_key_s;
  errno = 0;
  key = strtol(key_s, &end_key_s, 10);
  if (errno != 0)
    return 1;
  if (key < 1 || key > 25)
    return 1;

  // Perform Caesar Encryption: CaesarEncrypt(key, plaintext) and print out the
  // ciphertext.
  ciphertext = CaesarEncrypt(key, plaintext);
  printf("Ciphertext: %s\n", ciphertext);

  // Perform Caesar Decryption: CaesarDecrypt(key, ciphertext) and print out the
  // decrypted ciphertext(decrypttext).
  decrypttext = CaesarDecrypt(key, ciphertext);
  printf("Decrypted plaintext: %s\n", decrypttext);
}

char *CaesarEncrypt(int key, char *plaintext) {
  char *ret = (char *)malloc(sizeof(char) * 1024);
  int i;
  for (i = 0; i < 1024; i++) {
    ret[i] = plaintext[i];
    if (plaintext[i] == 0)
      break;
    if (plaintext[i] < 65)
      continue;
    else if (plaintext[i] <= 90)
      ret[i] = mod(ret[i] - 65 + key, 26) + 65;
    else if (plaintext[i] < 97)
      continue;
    else if (plaintext[i] <= 122)
      ret[i] = mod(ret[i] - 97 + key, 26) + 97;
  }
  return ret;
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
