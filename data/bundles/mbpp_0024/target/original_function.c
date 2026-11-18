int func0(int binary) {
  int binary1 = binary;
  int decimal = 0;
  int i = 0;
  while (binary != 0) {
    int dec = binary % 10;
    decimal += dec * (int)pow(2, i);
    binary /= 10;
    i++;
  }
  return decimal;
}