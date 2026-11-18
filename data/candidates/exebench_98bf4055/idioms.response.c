void reverseIntRange(int *start, int *end, int size)
{
  int temp = *start;
  *start = size - *end;
  *end = size - temp;
}