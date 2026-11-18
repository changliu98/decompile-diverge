char_u *__cdecl regtilde(char_u *source, int magic)
{
  size_t v2; // rax
  size_t v3; // rax
  size_t v4; // rax
  int prevlen; // [rsp+20h] [rbp-30h]
  int len; // [rsp+24h] [rbp-2Ch]
  char *p; // [rsp+28h] [rbp-28h]
  char_u *tmpsub; // [rsp+30h] [rbp-20h]
  char_u *newsub; // [rsp+38h] [rbp-18h]

  newsub = source;
  for ( p = (char *)source; *p; ++p )
  {
    if ( *p == 126 && magic || *p == 92 && p[1] == 126 && !magic )
    {
      if ( reg_prev_sub )
      {
        prevlen = strlen(reg_prev_sub);
        v2 = strlen((const char *)newsub);
        tmpsub = (char_u *)alloc(prevlen + v2);
        if ( tmpsub )
        {
          len = (_DWORD)p - (_DWORD)newsub;
          memmove(tmpsub, newsub, (int)p - (int)newsub);
          memmove(&tmpsub[(int)p - (int)newsub], reg_prev_sub, prevlen);
          if ( !magic )
            ++p;
          strcpy((char *)&tmpsub[len + prevlen], p + 1);
          if ( newsub != source )
            QScopedPointerPodDeleter::cleanup(newsub);
          newsub = tmpsub;
          p = (char *)&tmpsub[len + prevlen];
        }
      }
      else if ( magic )
      {
        v3 = strlen(p + 1);
        memmove(p, p + 1, v3 + 1);
      }
      else
      {
        v4 = strlen(p + 2);
        memmove(p, p + 2, v4 + 1);
      }
      --p;
    }
    else
    {
      if ( *p == 92 && p[1] )
        ++p;
      if ( has_mbyte )
        p += (int)(mb_ptr2len(p) - 1);
    }
  }
  QScopedPointerPodDeleter::cleanup(reg_prev_sub);
  reg_prev_sub = (char *)vim_strsave(newsub);
  return newsub;
}