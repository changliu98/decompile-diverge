void func0(char *sentence, char *out)
{
  int i; int j; int word_len = 0; int out_index = 0;
  int is_prime;
  for (i = 0; sentence[i]; i++)
  {
    if (sentence[i] == ' ')
    {
      if (word_len > 1)
      {
        is_prime = 1;
        for (j = 2; j * j <= word_len; j++)
        {
          if (word_len % j == 0)
          {
            is_prime = 0;
            break;
          }
        }
      }
      else
      {
        is_prime = 0;
      }
      if (is_prime)
      {
        if (out_index > 0)
        {
          out[out_index++] = ' ';
        }
        memcpy(&out[out_index], &sentence[i - word_len], word_len);
        out_index += word_len;
      }
      word_len = 0;
    }
    else
    {
      word_len++;
    }
  }
  if (word_len > 1)
  {
    is_prime = 1;
    for (j = 2; j * j <= word_len; j++)
    {
      if (word_len % j == 0)
      {
        is_prime = 0;
        break;
      }
    }
  }
  else
  {
    is_prime = 0;
  }
  if (is_prime)
  {
    if (out_index > 0)
    {
      out[out_index++] = ' ';
    }
    memcpy(&out[out_index], &sentence[i - word_len], word_len);
    out_index += word_len;
  }
  out[out_index] = '\0';
}