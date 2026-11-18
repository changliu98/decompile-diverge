char *
isis_print_id(const uint8_t *cp, int id_len)
{
 char *pos = isis_print_id::id;
 int i;

 for (i = 1; i <= 6; i++) {
  snprintf(pos, sizeof(isis_print_id::id) - (pos - isis_print_id::id),
    "%02x", *cp);
  pos += strlen(pos);
  if (i == 2 || i == 4)
   *pos++ = '.';
  cp++;
 }
 if (id_len > 6) {
  snprintf(pos, sizeof(isis_print_id::id) - (pos - isis_print_id::id),
    ".%02x", *cp);
  pos += strlen(pos);
  cp++;
 }
 if (id_len == 8)
  snprintf(pos, sizeof(isis_print_id::id) - (pos - isis_print_id::id),
    "-%02x", *cp);

 return isis_print_id::id;
}