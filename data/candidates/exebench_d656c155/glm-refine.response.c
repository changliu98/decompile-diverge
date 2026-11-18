int __cdecl convertToBills(int dollars, int *hds, int *fts, int *tts, int *tns)
{
  *hds = dollars / 100;
  dollars %= 100;

  *fts = dollars / 50;
  dollars %= 50;

  *tts = dollars / 20;
  dollars %= 20;

  *tns = dollars / 10;
  dollars %= 10;

  return dollars;
}