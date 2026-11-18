void func0(int *arr, int len) {
 int i, out_of_place = -1;

 for (i = 0; i < len; i++) {
  if (out_of_place >= 0) {
   if ((arr[i] >= 0 && arr[out_of_place] < 0) ||
    (arr[i] < 0 && arr[out_of_place] >= 0)) {
    right_rotate(arr, len, out_of_place, i);

    if (i - out_of_place > 2) {
     out_of_place += 2;
    } else {
     out_of_place = -1;
    }
   }
  } else {
   if ((arr[i] >= 0 && i % 2 == 0) || (arr[i] < 0 && i % 2 == 1)) {
    out_of_place = i;
   }
  }
 }
}