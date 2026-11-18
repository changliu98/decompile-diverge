void to_upper(int *chptr)
{
  int ch = *chptr;
  if (ch >= 'a' && ch <= 'i')
    *chptr = ch - 'a' + 'A';
  else if (ch >= 'j' && ch <= 'r')
    *chptr = ch - 'j' + 'J';
  else if (ch >= 's' && ch <= 'z')
    *chptr = ch - 's' + 'S';
}