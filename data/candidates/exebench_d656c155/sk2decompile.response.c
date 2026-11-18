int convertToBills(int amount, int *num100, int *num50, int *num20,
                   int *num10) {
  *num100 = amount / 100;
  amount = amount % 100;
  *num50 = amount / 50;
  amount = amount % 50;
  *num20 = amount / 20;
  amount = amount % 20;
  *num10 = amount / 10;
  amount = amount % 10;
  return amount;
}