int lowercase(int ch)
{
  if (ch >= 'A' && ch <= 'Z')
    return (ch - 'A') + 'a';
  else
    return ch;
}