int func0(int actual_cost,int sale_amount)

{
  int sale_amount_local;
  int actual_cost_local;
  undefined4 local_c;
  
  if (sale_amount < actual_cost) {
    local_c = actual_cost - sale_amount;
  }
  else {
    local_c = -1;
  }
  return local_c;
}