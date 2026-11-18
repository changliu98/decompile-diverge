void __cdecl string_rip(char *str, const char *ripper)
{
  char *v2; // rax
  char v3; // cl
  char *v4; // rax
  int skip_this; // [rsp+0h] [rbp-24h]
  const char *ripper_idx; // [rsp+4h] [rbp-20h]
  char *t_ptr; // [rsp+Ch] [rbp-18h]
  char *stra; // [rsp+1Ch] [rbp-8h]

  stra = str;
  t_ptr = str;
  while ( *stra )
  {
    ripper_idx = ripper;
    skip_this = 0;
    while ( *ripper_idx )
    {
      if ( *stra == *ripper_idx )
      {
        skip_this = 1;
        break;
      }
      ++ripper_idx;
    }
    if ( skip_this )
    {
      ++stra;
    }
    else
    {
      v2 = stra++;
      v3 = *v2;
      v4 = t_ptr++;
      *v4 = v3;
    }
  }
  *t_ptr = 0;
}