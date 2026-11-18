void __cdecl func0(const char *sentence, char *out)
{
  int v2; // ecx
  int v3; // ecx
  int j; // [rsp+8h] [rbp-28h]
  int ja; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  bool is_prime; // [rsp+13h] [rbp-1Dh]
  bool is_primea; // [rsp+13h] [rbp-1Dh]
  int out_index; // [rsp+14h] [rbp-1Ch]
  int word_len; // [rsp+18h] [rbp-18h]

  word_len = 0;
  out_index = 0;
  for ( i = 0; sentence[i]; ++i )
  {
    if ( sentence[i] == 32 )
    {
      if ( word_len <= 1 )
      {
        is_prime = 0;
      }
      else
      {
        is_prime = 1;
        for ( j = 2; j * j <= word_len; ++j )
        {
          if ( !(word_len % j) )
          {
            is_prime = 0;
            break;
          }
        }
      }
      if ( is_prime )
      {
        if ( out_index > 0 )
        {
          v2 = out_index++;
          out[v2] = 32;
        }
        memcpy(&out[out_index], &sentence[i - word_len], word_len);
        out_index += word_len;
      }
      word_len = 0;
    }
    else
    {
      ++word_len;
    }
  }
  if ( word_len <= 1 )
  {
    is_primea = 0;
  }
  else
  {
    is_primea = 1;
    for ( ja = 2; ja * ja <= word_len; ++ja )
    {
      if ( !(word_len % ja) )
      {
        is_primea = 0;
        break;
      }
    }
  }
  if ( is_primea )
  {
    if ( out_index > 0 )
    {
      v3 = out_index++;
      out[v3] = 32;
    }
    memcpy(&out[out_index], &sentence[i - word_len], word_len);
    out_index += word_len;
  }
  out[out_index] = 0;
}