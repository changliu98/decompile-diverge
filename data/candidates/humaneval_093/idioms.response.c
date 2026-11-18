void func0(char *in, char *out)
{
  int i; int j;
  char c;
  for (i = 0; in[i]; i++) {
    c = in[i];
    if (((*__ctype_b_loc ())[(int) ((c))] & (unsigned short) _ISlower))
      c = toupper(c);
    else if (((*__ctype_b_loc ())[(int) ((c))] & (unsigned short) _ISupper))
      c = tolower(c);
    for (j = 0; aAeiouaeiou[j]; j++) {
      if (c == aAeiouaeiou[j]) {
        if (j < 10)
          c += 2;
        break;
      }
    }
    out[i] = c;
  }
  out[i] = '\0';
}