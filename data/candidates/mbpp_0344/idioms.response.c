int func0(int start, int end){
 int sqrt_end = (int)sqrt(end);
 int sqrt_start = (int)sqrt(start - 1);
 return sqrt_end - sqrt_start;
}