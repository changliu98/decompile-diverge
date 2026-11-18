int factors(int M, int *arr)
{
 int i = 0;
 int num = 2;

 while (M % 53 == 0) { arr[i++] = 53; M /= 53; }
 while (M % 47 == 0) { arr[i++] = 47; M /= 47; }
 while (M % 43 == 0) { arr[i++] = 43; M /= 43; }
 while (M % 41 == 0) { arr[i++] = 41; M /= 41; }
 while (M % 37 == 0) { arr[i++] = 37; M /= 37; }
 while (M % 31 == 0) { arr[i++] = 31; M /= 31; }
 while (M % 29 == 0) { arr[i++] = 29; M /= 29; }
 while (M % 23 == 0) { arr[i++] = 23; M /= 23; }
 while (M % 19 == 0) { arr[i++] = 19; M /= 19; }
 while (M % 17 == 0) { arr[i++] = 17; M /= 17; }
 while (M % 13 == 0) { arr[i++] = 13; M /= 13; }
 while (M % 11 == 0) { arr[i++] = 11; M /= 11; }
 while (M % 8 == 0) { arr[i++] = 8; M /= 8; }
 while (M % 7 == 0) { arr[i++] = 7; M /= 7; }
 while (M % 5 == 0) { arr[i++] = 5; M /= 5; }
 while (M % 4 == 0) { arr[i++] = 4; M /= 4; }
 while (M % 3 == 0) { arr[i++] = 3; M /= 3; }
 while (M % 2 == 0) { arr[i++] = 2; M /= 2; }

 if (M > 31)
 {
  while (M > 1)
  {
   int n1 = 6 * num - 1;
   int n2 = 6 * num + 1;

   while (M % n1 == 0) { arr[i++] = n1; M /= n1; }
   while (M % n2 == 0) { arr[i++] = n2; M /= n2; }

   num++;
  }
 }

 return i;
}