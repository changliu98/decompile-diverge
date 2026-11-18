boolean func0(int *test_tuple, int tuple_size, int *K, int K_size) {

 int i, j;
 boolean found;

 for (i = 0; i < tuple_size; i++) {
  found = false;
  for (j = 0; j < K_size; j++) {
   if (test_tuple[i] == K[j]) {
    found = true;
    break;
   }
  }
  if (!found)
   return false;
 }

 return true;
}