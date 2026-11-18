void unhide(char * Tekst) {
 int i, j = 0;
 int Oile[3] = {3, 1, 2};
 for (i = 0; ; i++) {
  if (Tekst[i] == '\0') break;
  Tekst[i] -= Oile[j];
  j++;
  if (j == 3) j = 0;
 }
}