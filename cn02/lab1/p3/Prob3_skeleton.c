#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct incidence_pair {
  char c[26];      // Letter in the cipher text
  double freq[26]; // Incidence percentage of each letter
};

// Computing a histogram of the incidence each letter (ignoring all non alphabet
// characters).
struct incidence_pair getIncidence(char *);

// Takes a partial mono-alphabetic substitution (subs) and a ciphertext and
// returns a potential plaintext.
char *monoalphabetic_substitution(char *, char *);

int main(int argc, char *argv[]) {
  char ciphertext[1024] =
      "ztmn pxtne cfa peqef kecnp cjt tmn zcwsenp ontmjsw ztnws tf wsvp "
      "xtfwvfefw, c feb fcwvtf, xtfxevqea vf gvoenwk, cfa aeavxcwea wt wse "
      "rntrtpvwvtf wscw cgg lef cne xnecwea eymcg";
  char plaintext[1024] = "";
  char subs[26] = "";

  struct incidence_pair ip = getIncidence(ciphertext);

  if (argc != 2) {
    printf("Not enough or too many arguments!\n");
    exit(1);
  }
  strcpy(subs, argv[1]);
  if (strcmp(subs, "") == 0)
    for (int i = 0; i < 26; i++)
      printf("%c:%5f\n", ip.c[i], ip.freq[i]);

  strcpy(plaintext, monoalphabetic_substitution(ciphertext, subs));
  printf("Potential Plaintext: %s\n", plaintext);
  return 0;
}

struct incidence_pair getIncidence(char *ciphertext) {
  int i, incidences[26] = {};
  for (i = 0; ciphertext[i] != 0; i++)
    if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
      incidences[ciphertext[i] - 'a']++;
  int len = i; // Store the length of ciphertext.
  struct incidence_pair ip;
  for (int i = 0; i < 26; i++) {
    int maxi = 0;
    for (int j = 0; j < 26; j++)
      maxi = incidences[maxi] < incidences[j] ? j : maxi;
    ip.c[i] = maxi + 'a';
    ip.freq[i] = (double)incidences[maxi] / (double)len;
    incidences[maxi] = -1;
  }
  return ip;
}

char *monoalphabetic_substitution(char *ciphertext, char *subs) {
  size_t len = strlen(ciphertext);
  char *ret = malloc(sizeof(char) * len + 1);
  for (int i = 0; i <= (int)len; i++)
    ret[i] = ciphertext[i] >= 'a' && ciphertext[i] <= 'z' &&
                     subs[ciphertext[i] - 'a'] != 0 &&
                     subs[ciphertext[i] - 'a'] != '_'
                 ? subs[ciphertext[i] - 'a']
                 : ciphertext[i];
  return ret;
}
