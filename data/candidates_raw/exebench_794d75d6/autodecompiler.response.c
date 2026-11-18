static void
adjust_offset(int *offset, int *length, int *pos, int end)
{
 if (*offset < 0) {
  *pos += *offset;
  *length -= *offset;
  *offset = 0;
 }
 if (*offset + *pos > end)
  *pos = end - *offset;
}