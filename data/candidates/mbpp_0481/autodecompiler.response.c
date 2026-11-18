int func0(int array[], int sizeofarray, int m)
{
 char result;
 if(m==0) result = 1;
 else if(sizeofarray==0) result = 0;
 else if(array[sizeofarray-1]>m)
 {
  result = func0(array,sizeofarray-1,m)&1;
 }
 else
 {
  char c1,c2;
  c1 = func0(array,sizeofarray-1,m)&1;
  c2 = func0(array,sizeofarray-1,m-array[sizeofarray-1]);
  result = c1&1|c2&1;
 }
 return result&1;
}