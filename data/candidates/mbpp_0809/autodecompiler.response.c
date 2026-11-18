int func0(int *tuple1, int *tuple2, int len) {
  char result = 1;
  int i = 0;
  while(1) {
    if(i >= len) break;
    if(tuple1[i] <= tuple2[i]) {
      result = 0;
      break;
    }
    i++;
  }
  return result & 1;
}