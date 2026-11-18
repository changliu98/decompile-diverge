int summe(int *zahl, int *summe)
{
  int ret = 1;
  if(*zahl == 0)
    ret = 0;
  else
  {
    *summe += *zahl;
    *zahl = *zahl - 1;
    ret = summe(&(*zahl), &(*summe)) != 0;
  }
  return ret;
}