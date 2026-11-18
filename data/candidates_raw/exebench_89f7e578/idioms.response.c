void sios_id2name(char *name, unsigned int id, unsigned char len)
{
 char *ptr = name;
 if (len >= 5) {
  ptr += 1;
  *(unsigned short *)ptr = (id / (10 * 10 * 10 * 10 * 10) % 10 + 16) |
   (1 << 10);
 }
 if (len >= 4) {
  ptr += 1;
  *(unsigned short *)ptr = (id / (10 * 10 * 10 * 10) % 10 + 16) |
   (1 << 10);
 }
 if (len >= 3) {
  ptr += 1;
  *(unsigned short *)ptr = (id / (10 * 10 * 10) % 10 + 16) |
   (1 << 10);
 }
 if (len >= 2) {
  ptr += 1;
  *(unsigned short *)ptr = (id / (10 * 10) % 10 + 16) |
   (1 << 10);
 }
 if (len >= 1) {
  ptr += 1;
  *(unsigned short *)ptr = (id / (10) % 10 + 16) | (1 << 10);
 }
}