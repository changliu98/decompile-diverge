sds __cdecl sdscatrepr(sds s, const char *p, size_t len)
{
  int v5; // [rsp+4h] [rbp-1Ch]
  char *sa; // [rsp+18h] [rbp-8h]

  sa = sdscatlen(s, "\"", 1uLL);
  while ( len-- )
  {
    v5 = *p;
    switch ( v5 )
    {
      case 7:
        sa = sdscatlen(sa, "\\a", 2uLL);
        break;
      case 8:
        sa = sdscatlen(sa, "\\b", 2uLL);
        break;
      case 9:
        sa = sdscatlen(sa, "\\t", 2uLL);
        break;
      case 10:
        sa = sdscatlen(sa, "\\n", 2uLL);
        break;
      case 13:
        sa = sdscatlen(sa, "\\r", 2uLL);
        break;
      case 34:
      case 92:
        sa = sdscatprintf(sa, "\\%c", (unsigned int)*p);
        break;
      default:
        if ( ((*__ctype_b_loc())[*p] & 0x4000) != 0 )
          sa = sdscatprintf(sa, "%c", (unsigned int)*p);
        else
          sa = sdscatprintf(sa, "\\x%02x", *(unsigned __int8 *)p);
        break;
    }
    ++p;
  }
  return sdscatlen(sa, "\"", 1uLL);
}