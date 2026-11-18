void get_size(unsigned long size, unsigned long *nsize, char *size_str)
{
  int i = 0;
  while (size > 1024) {
    size = size / 1024;
    i++;
  }
  switch (i) {
    case 0:
      *size_str = ' ';
      break;
    case 1:
      *size_str = 'K';
      break;
    case 2:
      *size_str = 'M';
      break;
    case 3:
      *size_str = 'G';
      break;
    case 4:
      *size_str = 'T';
      break;
    case 5:
      *size_str = 'P';
      break;
  }
  *nsize = size;
}