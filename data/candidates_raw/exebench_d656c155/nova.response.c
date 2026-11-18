int func0(int n, int *pennies, int *nickels, int *dimes, int *quarters,
          int *half_dollars) {
    *pennies = n / 100;
    *nickels = (n % 100) / 20;
    *dimes = (n % 20) / 10;
    *quarters = (n % 10) / 5;
    *half_dollars = (n % 5) / 1;
    return n % 1;
}