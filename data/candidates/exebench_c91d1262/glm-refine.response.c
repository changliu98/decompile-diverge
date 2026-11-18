int __cdecl ISORegexp__get_cclass(char *pattern, int ppos, int *len, int *from, int *to, int *reverse)
{
  int current_pos;
  int next_pos;
  int ret_type;

  // Check for negation/reverse caret '^'
  if (pattern[ppos] == '^')
  {
    current_pos = ppos + 1;
    *reverse = 1;
  }
  else
  {
    current_pos = ppos;
    *reverse = 0;
  }

  switch (pattern[current_pos])
  {
    case ' ':
      *len = 1;
      return 3;

    case '%':
      next_pos = current_pos + 1;
      *len = 2;
      switch (pattern[next_pos])
      {
        case 'C': ret_type = 4; break;
        case 'P': ret_type = 7; break;
        case 'c': ret_type = 1; break;
        case 'd': ret_type = 2; break;
        case 'i': ret_type = 5; break;
        case 'p': ret_type = 6; break;
        case 't': ret_type = 9; break;
        default:
          *from = next_pos;
          *to = next_pos;
          ret_type = 8;
          break;
      }
      return ret_type;

    case '[':
      *from = current_pos + 2;
      while (pattern[current_pos] != '\0' && pattern[current_pos] != ']')
      {
        ++current_pos;
      }
      *to = current_pos - 1;
      *len = current_pos - *from + 1;
      return 8;

    default:
      *len = 1;
      *from = current_pos;
      *to = current_pos;
      return 8;
  }
}