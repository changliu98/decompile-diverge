int __cdecl utoa(char *str, unsigned int u, int spec)
{
  char *v3; // rax
  char *v4; // rax
  char v5; // cl
  char *v6; // rax
  char v7; // cl
  char *v8; // rax
  char *hex; // [rsp+Ch] [rbp-F8h]
  char hexupper[17]; // [rsp+14h] [rbp-F0h] BYREF
  char hexlower[17]; // [rsp+34h] [rbp-D0h] BYREF
  int base; // [rsp+48h] [rbp-BCh]
  char *s; // [rsp+4Ch] [rbp-B8h]
  char *p; // [rsp+54h] [rbp-B0h]
  char *end; // [rsp+5Ch] [rbp-A8h]
  char tmp[128]; // [rsp+64h] [rbp-A0h] BYREF
  char v18; // [rsp+E4h] [rbp-20h] BYREF
  int speca; // [rsp+ECh] [rbp-18h]
  unsigned int ua; // [rsp+F0h] [rbp-14h]
  char *stra; // [rsp+F4h] [rbp-10h]
  int v22; // [rsp+100h] [rbp-4h]

  stra = str;
  ua = u;
  speca = spec;
  end = &v18;
  p = &tmp[127];
  s = str;
  strcpy(hexlower, "0123456789abcdef");
  strcpy(hexupper, "0123456789ABCDEF");
  switch ( spec )
  {
    case 'X':
      base = 16;
      hex = hexupper;
      goto LABEL_7;
    case 'd':
    case 'i':
    case 'u':
      base = 10;
      goto LABEL_7;
    case 'o':
      base = 8;
      goto LABEL_7;
    case 'x':
      base = 16;
      hex = hexlower;
      do
      {
LABEL_7:
        switch ( base )
        {
          case 8:
            v3 = p--;
            *v3 = (ua & 7) + 48;
            break;
          case 10:
            v4 = p--;
            *v4 = ua % 0xA + 48;
            break;
          case 16:
            v5 = hex[ua & 0xF];
            v6 = p--;
            *v6 = v5;
            break;
        }
        ua /= (unsigned int)base;
      }
      while ( ua );
      ++p;
      while ( p < end )
      {
        v7 = *p;
        v8 = s++;
        *v8 = v7;
        ++p;
      }
      *s = 0;
      v22 = (_DWORD)s - (_DWORD)stra;
      break;
    default:
      v22 = -1;
      break;
  }
  return v22;
}