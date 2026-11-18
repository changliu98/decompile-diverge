static int sdsHdrSize(unsigned char type) {
  int hdrlen;
  switch (type & 7) {
    case 0:
      hdrlen = 1;
      break;
    case 1:
      hdrlen = 3;
      break;
    case 2:
      hdrlen = 5;
      break;
    case 3:
      hdrlen = 9;
      break;
    case 4:
      hdrlen = 17;
      break;
    default:
      hdrlen = 0;
      break;
  }
  return hdrlen;
}