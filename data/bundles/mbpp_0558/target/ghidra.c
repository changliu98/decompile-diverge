int func0(int n1,int n2)

{
  int sum;
  int distance;
  int n2_local;
  int n1_local;
  
  distance = abs(n1 - n2);
  sum = 0;
  for (; 0 < distance; distance = distance / 10) {
    sum = distance % 10 + sum;
  }
  return sum;
}