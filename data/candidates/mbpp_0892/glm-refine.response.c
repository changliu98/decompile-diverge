char *__cdecl func0(const char *text)
{
  char *buf_ptr;          // rax
  char *out_ptr;          // [rsp+8h] [rbp-68h]
  const char *in_ptr;     // [rsp+10h] [rbp-60h]
  regmatch_t match;       // [rsp+18h] [rbp-58h] BYREF
  regex_t regex;          // [rsp+20h] [rbp-50h] BYREF

  in_ptr = text;
  out_ptr = (char *)&func0_buffer;
  
  // Compile regex to match one or more spaces (" +")
  if ( regcomp(&regex, " +", 1) )
    return 0LL;

  // Iterate through the input string until the null terminator is reached
  while ( *in_ptr )
  {
    // If no more matches are found, copy the rest of the string and break
    if ( regexec(&regex, in_ptr, 1uLL, &match, 0) )
    {
      strcpy(out_ptr, in_ptr);
      break;
    }
    
    // Copy the characters before the matched spaces
    memcpy(out_ptr, in_ptr, match.rm_so);
    
    // Advance the output pointer and replace the matched spaces with a single space
    out_ptr += match.rm_so;
    *out_ptr++ = 32;  // 32 is the ASCII code for ' '
    
    // Advance the input pointer past the matched spaces
    in_ptr += match.rm_eo;
  }
  
  regfree(&regex);
  return (char *)&func0_buffer;
}