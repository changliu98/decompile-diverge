static bool nsgif__deinterlace(int height, int *row, unsigned char *flags) {
  *row += *flags & 0x0f;
  if (*row >= height) {
    switch (*flags) {
      case 4:
        *row = 1;
        *flags = 2;
        break;
      case 8:
        *row = 2;
        *flags = 4;
        break;
      case 24:
        *row = 4;
        *flags = 8;
        break;
      default:
        return false;
    }
  }
  return *row < height;
}