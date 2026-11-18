void convert_human(uint64_t size, uint64_t *nsize, char *c)
{
 int i;

 for (i = 0; size > 1024; i++)
  size >>= 10;

 switch (i) {
 case 0:
  *c = ' ';
  break;
 case 1:
  *c = 'K';
  break;
 case 2:
  *c = 'M';
  break;
 case 3:
  *c = 'G';
  break;
 case 4:
  *c = 'T';
  break;
 case 5:
  *c = 'P';
  break;
 }

 *nsize = size;
}