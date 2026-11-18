void __cdecl strip(char *str)
{
  int read_pos; // ecx
  int write_pos; // ecx
  int compaction_start; // [rsp+0h] [rbp-20h]
  int first_redundant; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]
  int ia; // [rsp+14h] [rbp-Ch]

  if ( str )
  {
    // Phase 1: Mark duplicate characters with -1
    for ( i = 1; str[i]; ++i )
    {
      for ( j = 0; j < i; ++j )
      {
        if ( str[j] == str[i] )
        {
          str[i] = -1;
          break;
        }
      }
    }
    
    first_redundant = 0;
    compaction_start = 0;
    
    // Phase 2: Find the first marked character to start the compaction phase
    for ( ia = 1; str[ia]; ++ia )
    {
      if ( str[ia] == -1 )
      {
        first_redundant = ia;
        while ( str[ia] == -1 )
          ++ia;
        compaction_start = ia;
        break;
      }
    }
    
    // Phase 3: Compact the string by overwriting marked (-1) characters 
    // with valid characters found later in the string
    if ( first_redundant )
    {
      while ( str[compaction_start] )
      {
        if ( str[compaction_start] == -1 )
        {
          ++compaction_start;
        }
        else
        {
          read_pos = first_redundant++;
          str[read_pos] = str[compaction_start];
          write_pos = compaction_start++;
          str[write_pos] = -1;
        }
      }
      str[first_redundant] = 0;
    }
  }
}