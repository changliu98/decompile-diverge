int func0(int A,int B)

{
  int i;
  int variable;
  int B_local;
  int A_local;
  undefined4 local_c;
  
  variable = 1;
  if (A == B) {
    local_c = 1;
  }
  else {
    i = A;
    if (B - A < 5) {
      while (i = i + 1, i <= B) {
        variable = (variable * (i % 10)) % 10;
      }
      local_c = variable % 10;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}