int __cdecl descape(int *in, int *out)
{
  int v3; // [rsp+1Ch] [rbp-4h]

  if ( *in == 92 )
  {
    switch ( in[1] )
    {
      case '"':
        out[1] = 34;
        v3 = 1;
        break;
      case '\'':
        out[1] = 39;
        v3 = 1;
        break;
      case '?':
        out[1] = 63;
        v3 = 1;
        break;
      case 'a':
        out[1] = 7;
        v3 = 1;
        break;
      case 'b':
        out[1] = 8;
        v3 = 1;
        break;
      case 'f':
        out[1] = 12;
        v3 = 1;
        break;
      case 'n':
        out[1] = 10;
        v3 = 1;
        break;
      case 'r':
        out[1] = 13;
        v3 = 1;
        break;
      case 't':
        out[1] = 9;
        v3 = 1;
        break;
      case 'v':
        out[1] = 11;
        v3 = 1;
        break;
      default:
        goto LABEL_13;
    }
  }
  else
  {
LABEL_13:
    *out = *in;
    out[1] = in[1];
    return 0;
  }
  return v3;
}