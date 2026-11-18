int __cdecl escape(char *fmt, int percent, size_t *len)
{
  char *v3; // rax
  char v4; // al
  char v5; // al
  char *v6; // rax
  bool v8; // [rsp+0h] [rbp-42h]
  bool v9; // [rsp+1h] [rbp-41h]
  int value; // [rsp+Ah] [rbp-38h]
  char c; // [rsp+11h] [rbp-31h]
  char ca; // [rsp+11h] [rbp-31h]
  char *store; // [rsp+12h] [rbp-30h]
  char *fmta; // [rsp+32h] [rbp-10h]

  fmta = fmt;
  store = fmt;
  while ( 2 )
  {
    c = *fmta;
    if ( !*fmta )
    {
      *store = 0;
      *len = store - fmt;
      return 0;
    }
    if ( c != 92 )
    {
      *store = c;
      goto LABEL_33;
    }
    v3 = fmta++;
    switch ( v3[1] )
    {
      case 0:
        *store = 92;
        store[1] = 0;
        *len = store + 1 - fmt;
        return 0;
      case 39:
      case 92:
        *store = *fmta;
        goto LABEL_33;
      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55:
        v9 = 0;
        if ( !percent )
          v9 = *fmta == 48;
        v4 = 3;
        if ( v9 )
          v4 = 4;
        ca = v4;
        for ( value = 0; ; value = 8 * value + *fmta++ - 48 )
        {
          v5 = ca--;
          v8 = 0;
          if ( v5 )
          {
            v8 = 0;
            if ( *fmta >= 48 )
              v8 = *fmta <= 55;
          }
          if ( !v8 )
            break;
        }
        --fmta;
        if ( percent && value == 37 )
        {
          v6 = store++;
          *v6 = 37;
          *store = 37;
        }
        else
        {
          *store = value;
        }
        goto LABEL_33;
      case 97:
        *store = 7;
        goto LABEL_33;
      case 98:
        *store = 8;
        goto LABEL_33;
      case 99:
        if ( percent )
        {
          *store = 99;
LABEL_33:
          ++fmta;
          ++store;
          continue;
        }
        *store = 0;
        *len = store - fmt;
        return 1;
      case 102:
        *store = 12;
        goto LABEL_33;
      case 110:
        *store = 10;
        goto LABEL_33;
      case 114:
        *store = 13;
        goto LABEL_33;
      case 116:
        *store = 9;
        goto LABEL_33;
      case 118:
        *store = 11;
        goto LABEL_33;
      default:
        *store = *fmta;
        goto LABEL_33;
    }
  }
}