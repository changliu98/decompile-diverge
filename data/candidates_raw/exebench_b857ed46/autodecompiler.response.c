static void
get_size(unsigned long size, unsigned long *out_size, char *out_unit)
{
 int i = 0;
 while (1) {
  if (size > 1024) {
   size /= 1024;
   i++;
  } else
   break;
 }
 int unit = i;
 switch (unit) {
 case 0:
  *out_unit = ' ';
  break;
 case 1:
  *out_unit = 'K';
  break;
 case 2:
  *out_unit = 'M';
  break;
 case 3:
  *out_unit = 'G';
  break;
 case 4:
  *out_unit = 'T';
  break;
 case 5:
  *out_unit = 'P';
 default:
  break;
 }
 *out_size = size;
}