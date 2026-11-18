char *func0(int array1[], int size1, int array2[], int size2)
{
 int i, j;
 int counter = 0;

 for(i = 0; i < size1; i++)
 {
  if(array1[i] % 2 == 0)
   counter++;
 }

 for(j = 0; j < size2; j++)
 {
  if(array2[j] % 2 == 0)
   counter++;
 }

 char *result;
 if(counter >= size1)
  result = "YES";
 else
  result = "NO";

 return result;
}