char *__cdecl url_canonize2(
        char *d,
        const char *const s,
        size_t n,
        unsigned int syn33,
        unsigned int m32,
        unsigned int m64,
        unsigned int m96)
{
  char v7; // al
  char v8; // al
  unsigned int v10; // [rsp+0h] [rbp-64h]
  unsigned int v11; // [rsp+4h] [rbp-60h]
  char v12; // [rsp+8h] [rbp-5Ch]
  char v13; // [rsp+14h] [rbp-50h]
  unsigned int v14; // [rsp+1Ch] [rbp-48h]
  unsigned int v15; // [rsp+20h] [rbp-44h]
  bool v16; // [rsp+27h] [rbp-3Dh]
  bool v17; // [rsp+28h] [rbp-3Ch]
  unsigned __int8 h2; // [rsp+29h] [rbp-3Bh]
  unsigned __int8 h1; // [rsp+2Ah] [rbp-3Ah]
  unsigned __int8 c; // [rsp+2Bh] [rbp-39h]
  unsigned __int8 ca; // [rsp+2Bh] [rbp-39h]
  size_t i; // [rsp+2Ch] [rbp-38h]
  char *da; // [rsp+54h] [rbp-10h]

  da = d;
  i = 0LL;
  if ( d == s )
  {
    while ( 1 )
    {
      v17 = 0;
      if ( s[i] )
        v17 = i < n;
      if ( !v17 || s[i] == 37 )
        break;
      ++da;
      ++i;
    }
  }
  while ( 1 )
  {
    v16 = 0;
    if ( s[i] )
      v16 = i < n;
    if ( !v16 )
      break;
    c = s[i];
    if ( c == 37 )
    {
      h1 = s[i + 1];
      if ( !h1 )
      {
        *da = 0;
        return 0LL;
      }
      h2 = s[i + 2];
      if ( (h1 < 0x30u || h1 > 0x39u) && (h1 < 0x41u || h1 > 0x46u) && (h1 < 0x61u || h1 > 0x66u)
        || (h2 < 0x30u || h2 > 0x39u) && (h2 < 0x41u || h2 > 0x46u) && (h2 < 0x61u || h2 > 0x66u) )
      {
        *da = 0;
        return 0LL;
      }
      if ( h1 < 0x61u )
      {
        v7 = 48;
        if ( h1 >= 0x41u )
          v7 = 55;
        v13 = v7;
      }
      else
      {
        v13 = 87;
      }
      if ( h2 < 0x61u )
      {
        v8 = 48;
        if ( h2 >= 0x41u )
          v8 = 55;
        v12 = v8;
      }
      else
      {
        v12 = 87;
      }
      ca = (h2 - v12) | (16 * (h1 - v13));
      if ( ca <= 0x20u
        || ca >= 0x7Fu
        || (ca >= 0x40u
          ? (ca >= 0x60u ? (v10 = (1 << (127 - ca)) & m96) : (v10 = (1 << (95 - ca)) & m64), v11 = v10)
          : (v11 = (1 << (63 - ca)) & m32),
            v11) )
      {
        if ( h1 >= 0x61u )
          h1 = h1 - 97 + 65;
        if ( h2 >= 0x61u )
          h2 = h2 - 97 + 65;
        *da = 37;
        da[1] = h1;
        da[2] = h2;
        da += 2;
        i += 2LL;
      }
      else
      {
        *da = ca;
        i += 2LL;
      }
    }
    else
    {
      if ( ((1 << (c - 33)) & syn33) == 0 )
      {
        if ( c <= 0x20u || c >= 0x7Fu )
          return 0LL;
        if ( c >= 0x40u )
        {
          v14 = c >= 0x60u ? (1 << (127 - c)) & m96 : (1 << (95 - c)) & m64;
          v15 = v14;
        }
        else
        {
          v15 = (1 << (63 - c)) & m32;
        }
        if ( v15 )
          return 0LL;
      }
      *da = c;
    }
    ++da;
    ++i;
  }
  *da = 0;
  return da;
}