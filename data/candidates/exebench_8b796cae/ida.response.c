int __cdecl unicode_to_utf8(char *buf, unsigned int c)
{
  char *v2; // rax
  char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  char *q; // [rsp+0h] [rbp-18h]
  char *qa; // [rsp+0h] [rbp-18h]
  char *qb; // [rsp+0h] [rbp-18h]
  char *qc; // [rsp+0h] [rbp-18h]
  char *qd; // [rsp+0h] [rbp-18h]

  if ( c >= 0x80 )
  {
    if ( c >= 0x800 )
    {
      if ( c >= 0x10000 )
      {
        if ( c >= 0x200000 )
        {
          if ( c >= 0x4000000 )
          {
            *buf = (c >> 30) | 0xFC;
            qd = buf + 2;
            buf[1] = HIBYTE(c) & 0x3F | 0x80;
          }
          else
          {
            qd = buf + 1;
            *buf = HIBYTE(c) | 0xF8;
          }
          v2 = qd;
          qc = qd + 1;
          *v2 = (c >> 18) & 0x3F | 0x80;
        }
        else
        {
          qc = buf + 1;
          *buf = (c >> 18) | 0xF0;
        }
        v3 = qc;
        qb = qc + 1;
        *v3 = (c >> 12) & 0x3F | 0x80;
      }
      else
      {
        qb = buf + 1;
        *buf = (c >> 12) | 0xE0;
      }
      v4 = qb;
      qa = qb + 1;
      *v4 = (c >> 6) & 0x3F | 0x80;
    }
    else
    {
      qa = buf + 1;
      *buf = (c >> 6) | 0xC0;
    }
    v5 = qa;
    q = qa + 1;
    *v5 = c & 0x3F | 0x80;
  }
  else
  {
    q = buf + 1;
    *buf = c;
  }
  *q = 0;
  return (_DWORD)q - (_DWORD)buf;
}