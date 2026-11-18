void
copy_header(char *s)
{
 char *t, *u;
 int c;

 strcat(IObuff, ": ");
 t = IObuff;
 u = s + strlen(IObuff);
 for (;;) {
  if (((c = *s) != '\0') && ((u - IObuff) < 1020 - 5)) {
   if ((enc_utf8 && (c == 0xC2) && (*(s + 1) == 0xA0))
       || (! enc_utf8 && (c == 0xA0))) {
    s += enc_utf8 ? 2 : 1;
    strcpy(u, "<a0>");
    u += 4;
    continue;
   }
   if (has_mbyte)
    mb_copy_char(&s, &u);
   else
    *u++ = *s++;
  } else
   break;
 }
 *u = '\0';
}