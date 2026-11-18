int decToBin(int dec, int *bin) {
  int dec_copy = dec;
  unsigned int pow = 1;
  int size = 0;
  while (pow <= dec) {
    pow *= 2;
    size++;
  }
  pow /= 2;
  size--;
  for (int i = size; i >= 0; i--) {
    if (dec_copy - pow >= 0) {
      dec_copy -= pow;
      bin[size - i] = 1;
    } else {
      bin[size - i] = 0;
    }
    pow /= 2;
  }
  return size;
}