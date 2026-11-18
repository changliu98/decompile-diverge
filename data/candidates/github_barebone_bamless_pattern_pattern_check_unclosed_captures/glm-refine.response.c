void __cdecl pattern_check_unclosed_captures(Pattern_State *ps)
{
  const char *pat_end;
  int pat_idx;

  // Find the end of the pattern string once to avoid calling strlen in the loop
  pat_end = ps->pattern_base + strlen(ps->pattern_base);

  // Start from 1 because capture groups are typically 1-indexed
  for ( int i = 1; i < ps->capture_count; ++i )
  {
    // A size of -1 indicates an unclosed capture group
    if ( ps->captures[i].size == -1 )
    {
      int open_captures = 0;
      
      for ( pat_idx = 0; &ps->pattern_base[pat_idx] < pat_end; )
      {
        char c = ps->pattern_base[pat_idx];
        
        if ( c == '%' )
        {
          // Skip escaped characters (e.g., %( or %%)
          pat_idx += 2;
        }
        else
        {
          if ( c == '(' && ++open_captures == i )
            break;
          ++pat_idx;
        }
      }
      
      // Report the error at the exact index of the unclosed '('
      pattern_set_error(ps, PATTERN_ERR_UNCLOSED_CAPTURE, pat_idx);
      return;
    }
  }
}