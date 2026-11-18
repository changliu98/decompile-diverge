static float binary_search( float value, float array[], int size )
{
   int low, high, mid;
   float x;

   if (value==array[0]) {
      return 0.0;
   }
   else if (value<array[0]) {
      return -1.0;
   }
   else if (value>array[size-1]) {
      return -1.0;
   }
   else if (value==array[size-1]) {
      return (float) (size-1);
   }
   else {

      low = 0;
      high = size-1;

      while (low<=high) {
         mid = (low+high)/2;
         if (value<array[mid])
           high = mid - 1;
         else if (value>array[mid])
           low = mid + 1;
         else
           return (float) mid;
      }


      x = (value-array[high]) / (array[low]-array[high]);
      return high * (1.0-x) + low * x;
   }
}