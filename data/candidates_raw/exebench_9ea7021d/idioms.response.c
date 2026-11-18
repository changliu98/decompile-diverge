void check_start_len(int *start, int *len, int max)
{
  if (*start < 0) {
    *len += *start;
    *start = 0;
  }
  if (*start + *len > max)
    *len = max - *start;
}