void func0(int *array, int length){
  int end;
  int temp;
  heapify(array, length);
  end = length - 1;
  while(end > 0){
    temp = array[end];
    array[end] = array[0];
    array[0] = temp;
    end--;
    shift_down(array, 0, end);
  }
}