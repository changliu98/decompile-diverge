int check_trend(float *data, int length)
{
 int i;
 int increasing = 0;
 int decreasing = 0;

 for (i = 1; ; i++) {
  if (i >= length) break;
  if (data[i] > data[i-1]) increasing = 1;
  if (data[i] < data[i-1]) decreasing = 1;
 }

 char result;
 if ((increasing + decreasing) == 2) result = 0;
 else result = 1;

 return (result & 1);
}