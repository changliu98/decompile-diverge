int max(int a, int b, int c, int *maxLocation)
{
 int max = 1;
 int tmpMax = a;

 if(tmpMax < b){
  tmpMax = b;
  max = 2;
 }

 if(tmpMax < c){
  tmpMax = c;
  max = 3;
 }

 *maxLocation = tmpMax;

 return max;
}