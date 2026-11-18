double func0(int n) {
 double sum = 0.0;
 int i = 1;
 while(1) {
  if(i > n) break;
  sum += (double)(i*i*i);
  ++i;
 }
 return round((sum / (double)n) * 1e6) / 1e6;
}