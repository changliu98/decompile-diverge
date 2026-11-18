int __cdecl LI_ltostr(char *buf, long val)
{
  char *v2; // rax
  int len; // [rsp+0h] [rbp-24h]
  int lena; // [rsp+0h] [rbp-24h]
  char *end; // [rsp+4h] [rbp-20h]
  char swap; // [rsp+13h] [rbp-11h]
  long vala; // [rsp+14h] [rbp-10h]
  char *bufa; // [rsp+1Ch] [rbp-8h]

  bufa = buf;
  vala = val;
  len = 1;
  if ( val < 0 )
  {
    len = 2;
    bufa = buf + 1;
    *buf = 45;
    vala = -val;
  }
  end = bufa;
  while ( vala > 9 )
  {
    v2 = end++;
    *v2 = vala % 10 + 48;
    vala /= 10LL;
  }
  *end = vala + 48;
  end[1] = 0;
  lena = (_DWORD)end - (_DWORD)bufa + len;
  while ( bufa < end )
  {
    swap = *end;
    *end = *bufa;
    *bufa++ = swap;
    --end;
  }
  return lena;
}