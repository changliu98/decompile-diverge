int getMax(int a, int b, int c, int *max)
{
 int choice = 1;
 int tmpMax = a;
 if(b > tmpMax){
  tmpMax = b;
  choice = 2;
 }
 if(c > tmpMax){
  tmpMax = c;
  choice = 3;
 }
 *max = tmpMax;
 return choice;
}