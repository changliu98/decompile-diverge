int func0(int n1,int n2)

{
  int setBits;
  int x;
  int n2_local;
  int n1_local;
  
  setBits = 0;
  for (x = n1 ^ n2; 0 < x; x = x >> 1) {
    setBits = (x & 1U) + setBits;
  }
  return setBits;
}