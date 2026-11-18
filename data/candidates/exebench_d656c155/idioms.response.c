int convertToBills(int dollars, int *hds, int *fts, int *tts, int *tns){
  *hds = dollars / 100;
  dollars = dollars % 100;
  *fts = dollars / 50;
  dollars = dollars % 50;
  *tts = dollars / 20;
  dollars = dollars % 20;
  *tns = dollars / 10;
  dollars = dollars % 10;
  return dollars;
}