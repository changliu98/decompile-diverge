int powerdigit(int base, int power){
  int digits[1000];
  int i; int j; int carry; int size = 1;
  long temp;
  digits[0] = 1;
  for (i = 0; i < power; i++){
    carry = 0;
    for (j = 0; j < size; j++){
      temp = (long)base * digits[j] + carry;
      digits[j] = (int)(temp % 10);
      carry = (int)(temp / 10);
    }
    while (carry > 0){
      digits[size] = carry % 10;
      carry = carry / 10;
      size++;
    }
  }
  int sum = 0;
  for (j = 0; j < size; j++)
    sum += digits[j];
  return sum;
}