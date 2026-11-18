void convert_human(unsigned int size, unsigned int *sizep, char *unitp) {
  int i = 0;
  while (size > 1024) {
    size /= 1024;
    i++;
  }
  switch (i) {
    case 0:
      *unitp = ' ';
      break;
    case 1:
      *unitp = 'K';
      break;
    case 2:
      *unitp = 'M';
      break;
    case 3:
      *unitp = 'G';
      break;
    case 4:
      *unitp = 'T';
      break;
    case 5:
      *unitp = 'P';
      break;
  }
  *sizep = size;
}