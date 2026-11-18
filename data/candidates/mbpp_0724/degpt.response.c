int func0(int base,int power)

{
  long lVar1;
  int i_1;
  int sum;
  long temp;
  int i;
  int carry;
  int p;
  int size;
  int digits [1000];
  int power_local;
  int base_local;
  
  size = 1;
  digits[0] = 1;
  for (p = 0; p < power; p = p + 1) {
    carry = 0;
    for (i = 0; i < size; i = i + 1) {
      lVar1 = (long)digits[i] * (long)base + (long)carry;
      digits[i] = (int)(lVar1 % 10);
      carry = (int)(lVar1 / 10);
    }
    for (; 0 < carry; carry = carry / 10) {
      digits[size] = carry % 10;
      size = size + 1;
    }
  }
  sum = 0;
  for (i_1 = 0; i_1 < size; i_1 = i_1 + 1) {
    sum = digits[i_1] + sum;
  }
  return sum;
}