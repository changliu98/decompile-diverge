int func0(int *array,int start,int end)

{
  int end_00;
  int mid;
  int end_local;
  int start_local;
  int *array_local;
  int local_c;
  
  if (end < start) {
    local_c = end + 1;
  }
  else {
    local_c = start;
    if (start == array[start]) {
      end_00 = (start + end) / 2;
      if (array[end_00] == end_00) {
        local_c = func0(array,end_00 + 1,end);
      }
      else {
        local_c = func0(array,start,end_00);
      }
    }
  }
  return local_c;
}