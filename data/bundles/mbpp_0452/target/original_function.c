int func0(int actual_cost, int sale_amount) {
  if (sale_amount > actual_cost) {
    int amount = sale_amount - actual_cost;
    return amount;
  } else {
    return 0;
  }
}