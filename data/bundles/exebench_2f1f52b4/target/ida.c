int __cdecl isLegalUTF8(const unsigned __int8 *source, int length)
{
  const unsigned __int8 *v2; // rax
  int v4; // [rsp+0h] [rbp-2Ch]
  const unsigned __int8 *srcptr; // [rsp+Ch] [rbp-20h]
  unsigned __int8 a; // [rsp+17h] [rbp-15h]
  unsigned __int8 aa; // [rsp+17h] [rbp-15h]
  unsigned __int8 ab; // [rsp+17h] [rbp-15h]

  srcptr = &source[length];
  switch ( length )
  {
    case 1:
      return (*source < 0x80u || *source >= 0xC2u) && *source <= 0xF4u;
    case 2:
      goto LABEL_9;
    case 3:
      goto LABEL_6;
    case 4:
      --srcptr;
      a = source[length - 1];
      if ( a < 0x80u || a > 0xBFu )
        return 0;
LABEL_6:
      v2 = srcptr--;
      aa = *(v2 - 1);
      if ( aa < 0x80u || aa > 0xBFu )
        return 0;
LABEL_9:
      ab = *(srcptr - 1);
      if ( ab > 0xBFu )
        return 0;
      v4 = *source;
      switch ( v4 )
      {
        case 224:
          if ( ab < 0xA0u )
            return 0;
          break;
        case 240:
          if ( ab < 0x90u )
            return 0;
          break;
        case 244:
          if ( ab > 0x8Fu )
            return 0;
          break;
        default:
          if ( ab < 0x80u )
            return 0;
          break;
      }
      return (*source < 0x80u || *source >= 0xC2u) && *source <= 0xF4u;
    default:
      return 0;
  }
}