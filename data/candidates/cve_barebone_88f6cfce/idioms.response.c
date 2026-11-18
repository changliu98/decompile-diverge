void append_command(char *cmd)
{
    char *p; char *q; char *end;
    int can_do;
    char *cp = cmd;
    p = cmd;
    out_text(IObuff, ": ");
    q = IObuff;
    end = q + get_iosize(IObuff);
    for (;;) {
 can_do = 1;
 if (*p)
     can_do = (end - IObuff) < (1024 - 10);
 if (!can_do)
     break;
 if (enc_utf8) {
     if (p[0] == 0xc2 && p[1] == 0xa0)
  continue;
     if (has_mbyte)
  utf8_to_mbyte(&p, &end);
     else
  *end++ = *p++;
 } else {
     if (p == " " || p == "\240") {
  p += (enc_utf8 ? 2 : 1);
  out_text(end, "<a0>");
  end += 4;
  continue;
     }
     if (has_mbyte)
  utf8_to_mbyte(&p, &end);
     else
  *end++ = *p++;
 }
    }
    *end = '\0';
}