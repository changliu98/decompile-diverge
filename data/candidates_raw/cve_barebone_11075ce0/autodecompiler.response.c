static char *isis_print_id(unsigned char *id, int idlen)
{
 static char isis_print_id_id[21];
 char *p;
 int i;

 p = isis_print_id_id;
 for (i = 1;; i++) {
  if (i <= 7) {
   snprintf(p, sizeof(isis_print_id_id) - (p - isis_print_id_id), "%02x",
     *id++);
   p += strlen(p);
   if (i == 2 || i == 4)
    *p++ = '.';
  } else {
   if (idlen >= 8) {
    snprintf(p, sizeof(isis_print_id_id) - (p - isis_print_id_id), ".%02x",
      *id++);
    p += strlen(p);
   }
   if (idlen == 8)
    snprintf(p, sizeof(isis_print_id_id) - (p - isis_print_id_id), "-%02x", *id);
   return isis_print_id_id;
  }
 }
}