void __cdecl pattern_check_unclosed_captures(Pattern_State *ps)
{
  const char *pat; // [rsp+18h] [rbp-18h]
  int captures; // [rsp+20h] [rbp-10h]
  int i; // [rsp+24h] [rbp-Ch]

  for ( i = 1; i < ps->capture_count; ++i )
  {
    if ( ps->captures[i].size == -1 )
    {
      captures = 0;
      pat = ps->pattern_base;
      while ( pat < &ps->pattern_base[strlen(ps->pattern_base)] )
      {
        if ( *pat == 37 )
        {
          pat += 2;
        }
        else
        {
          if ( *pat == 40 && ++captures == i )
            break;
          ++pat;
        }
      }
      pattern_set_error(ps, PATTERN_ERR_UNCLOSED_CAPTURE, pat - ps->pattern_base);
      return;
    }
  }
}