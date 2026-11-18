int LI_ltostr(char *buf, long val)
{
 char swap;
 char *end;
 int len = 1;


 if (val < 0)
 {
  len++;
  *(buf++) = '-';
  val = -val;
 }

 end = buf;
# 463 "buffer.c"
 while (val > 9)
 {
  *(end++) = '0' + (val % 10);
  val = val / 10;
 }
 *(end) = '0' + val;
 *(end + 1) = '\0';
 len += end - buf;


 while (buf < end)
 {
  swap = *end;
  *end = *buf;
  *buf = swap;

  buf++;
  end--;
 }

 return len;
}