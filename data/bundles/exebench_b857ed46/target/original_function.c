void convert_human(size_t size, size_t *nsize, char *c) {
 int p = 0;
 while (size > 1024) {
  size /= 1024;
  p++;
 }

 switch (p) {
  case 0: *c = ' '; break;
  case 1: *c = 'K'; break;
  case 2: *c = 'M'; break;
  case 3: *c = 'G'; break;
  case 4: *c = 'T'; break;
  case 5: *c = 'P'; break;
 }
 *nsize = size;
}