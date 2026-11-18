void byte_to_hex(char* dst, char src)
{
 if ((src / 16) >= 10)
 {
  dst[0] = ((src / 16) + 'A' - 10);
 }
 else
 {
  dst[0] = ((src / 16) + '0');
 }

 if ((src % 16) >= 10)
 {
  dst[1] = ((src % 16) + 'A' - 10);
 }
 else
 {
  dst[1] = ((src % 16) + '0');
 }
}