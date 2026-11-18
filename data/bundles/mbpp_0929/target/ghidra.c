int func0(int *tuplex,int size,int value)

{
  int i;
  int count;
  int value_local;
  int size_local;
  int *tuplex_local;
  
  count = 0;
  for (i = 0; i < size; i = i + 1) {
    if (tuplex[i] == value) {
      count = count + 1;
    }
  }
  return count;
}