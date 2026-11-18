int
enddata(char *buf, int len)
{
 int padlen, i, j;

 padlen = len % 64;
 j = len - padlen;
 if (padlen == 0) {
  i = 0;
 } else {
  buf[j + 1] = (char)(padlen - 1);
  len = j + 64;
  i = len;
 }
 return(i);
}