void __cdecl xmlrpc_char_encode(char *outbuffer, const char *s1)
{
  size_t v2; // rdx
  void (*append)(mowgli_string_ *, const char *, size_t); // [rsp+18h] [rbp-38h]
  mowgli_string_t *s; // [rsp+20h] [rbp-30h]
  char buf2[15]; // [rsp+28h] [rbp-28h] BYREF
  unsigned __int8 c; // [rsp+37h] [rbp-19h]
  unsigned __int64 i; // [rsp+38h] [rbp-18h]
  const char *s1a; // [rsp+40h] [rbp-10h]
  char *outbuffera; // [rsp+48h] [rbp-8h]

  outbuffera = outbuffer;
  s1a = s1;
  s = mowgli_string_create();
  buf2[0] = 0;
  *outbuffer = 0;
  if ( s1a && *s1a )
  {
    for ( i = 0LL; s1a[i]; ++i )
    {
      c = s1a[i];
      if ( c <= 0x7Fu )
      {
        switch ( c )
        {
          case '&':
            s->append(s, "&amp;", 5LL);
            break;
          case '<':
            s->append(s, "&lt;", 4LL);
            break;
          case '>':
            s->append(s, "&gt;", 4LL);
            break;
          case '"':
            s->append(s, "&quot;", 6LL);
            break;
          default:
            s->append_char(s, c);
            break;
        }
      }
      else
      {
        snprintf(buf2, 0xFuLL, "&#%d;", c);
        append = s->append;
        v2 = strlen(buf2);
        append(s, buf2, v2);
      }
    }
    memcpy(outbuffera, s->str, 0x1000uLL);
  }
}