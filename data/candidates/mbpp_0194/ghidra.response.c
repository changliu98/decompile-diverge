int func0(int n)

{
  int last_digit;
  int temp;
  int base;
  int dec_value;
  int num;
  int n_local;
  
  dec_value = 0;
  base = 1;
  for (temp = n; temp != 0; temp = temp / 10) {
    dec_value = (temp % 10) * base + dec_value;
    base = base << 3;
  }
  return dec_value;
}