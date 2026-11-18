static void
adjust_offset(int *offset, int *len, int max)
{
 if (*offset < 0) {
  *len += *offset;
  *offset = 0;
 }
 if (*offset + *len > max)
  *len = max - *offset;
}