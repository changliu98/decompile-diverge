int cp_unfilter(int w, int h, int bpp, unsigned char *data) {
  int i, j, size;
  unsigned char *f, *prev, *cur;
  size = w * bpp;
  if (h > 0) {
    f = data;
    data++;
    switch (*f) {
      case 0:
        break;
      case 1:
        for (i = bpp; i < size; i++) data[i] += data[i - bpp];
        break;
      case 2:
        break;
      case 3:
        for (i = bpp; i < size; i++) data[i] += data[i - bpp] / 2;
        break;
      case 4:
        for (i = bpp; i < size; i++) data[i] += cp_paeth(data[i - bpp], 0, 0);
        break;
      default:
        return 0;
    }
  }
  prev = data;
  data += size;
  for (j = 1; j < h; j++) {
    cur = data;
    data++;
    switch (*cur) {
      case 0:
        break;
      case 1:
        for (i = 0; i < bpp; i++) data[i] = data[i];
        for (; i < size; i++) data[i] += data[i - bpp];
        break;
      case 2:
        for (i = 0; i < bpp; i++) data[i] += prev[i];
        for (; i < size; i++) data[i] += prev[i];
        break;
      case 3:
        for (i = 0; i < bpp; i++) data[i] += prev[i] / 2;
        for (; i < size; i++) data[i] += (prev[i] + data[i - bpp]) / 2;
        break;
      case 4:
        for (i = 0; i < bpp; i++) data[i] += prev[i];
        for (; i < size; i++)
          data[i] += cp_paeth(data[i - bpp], prev[i], prev[i - bpp]);
        break;
      default:
        return 0;
    }
    prev = cur;
    data += size;
  }
  return 1;
}