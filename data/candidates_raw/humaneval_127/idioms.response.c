char *is_prime(int interval1_start, int interval1_end, int interval2_start, int interval2_end){
  int start;
  int end;
  int length;
  int i;
  int j;
  if(interval1_start > interval2_start){
    start = interval2_start;
  }
  else{
    start = interval1_start;
  }
  if(interval1_end < interval2_end){
    end = interval1_end;
  }
  else{
    end = interval2_end;
  }
  length = end - start;
  if(length < 2){
    return "not a prime";
  }
  for(i = 2; i*i <= length; i++){
    if(length % i == 0){
      return "not a prime";
    }
  }
  return "prime";
}