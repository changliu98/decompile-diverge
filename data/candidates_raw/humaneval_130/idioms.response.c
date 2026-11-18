int *get_all_ways(int n){
  int *all_ways = (int *)malloc((n + 1)*sizeof(int));
  int i;
  all_ways[0] = 1;
  if (n == 0){
    return all_ways;
  }
  all_ways[1] = 3;
  for (i = 2; i <= n; i++){
    if (i % 2 == 0){
      all_ways[i] = i / 2 + 1;
    }
    else{
      all_ways[i] = all_ways[i - 1] + all_ways[i - 2] + (i + 1)/2 + 1;
    }
  }
  return all_ways;
}