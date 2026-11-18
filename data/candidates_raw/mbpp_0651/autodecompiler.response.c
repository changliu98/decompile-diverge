int subset_tuple(int *tuple1, int cardinality1, int *tuple2, int cardinality2) {
  int i, j;
  char found;

  for(i = 0; i < cardinality2; i++) {
    found = 0;
    for(j = 0; j < cardinality1; j++) {
      if(tuple2[i] == tuple1[j]) {
 found = 1;
 break;
      }
    }
    if(!found)
      break;
  }

  return (i == cardinality2 ? 1 : 0);
}