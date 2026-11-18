int func0(int actual_cost,int sale_amount)

{
  int amount;
  int sale_amount_local;
  int actual_cost_local;
  undefined4 local_c;
  
  if (actual_cost < sale_amount) {
    local_c = sale_amount - actual_cost;
  }
  else {
    local_c = 0;
  }
  return local_c;
}