int func0(int x,int y,int z)

{
  bool bVar1;
  int j;
  int found;
  int i;
  int counts [3];
  int unique_values;
  int result [3];
  int z_local;
  int y_local;
  int x_local;
  int local_c;
  
  unique_values = 0;
  result[0] = x;
  result[1] = y;
  result[2] = z;
  memset(counts,0,0xc);
  i = 0;
  do {
    if (2 < i) {
      if (unique_values == 3) {
        local_c = 0;
      }
      else {
        local_c = 4 - unique_values;
      }
      return local_c;
    }
    bVar1 = false;
    for (j = 0; j < i; j = j + 1) {
      if (result[j] == result[i]) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      unique_values = unique_values + 1;
    }
    i = i + 1;
  } while( true );
}