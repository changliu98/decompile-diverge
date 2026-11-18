#include <stdio.h>

int convertToBills(int dollars, int *hds, int *fts, int *tts, int *tns) {
  *hds = dollars / 100;
  *fts = dollars % 100 / 50;
  *tts = dollars % 100 % 50 / 20;
  *tns = dollars % 100 % 50 % 20 / 10;

  return (dollars % 10);
}
