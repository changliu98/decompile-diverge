void lud_base(float *a)
{
   unsigned int i, j, k;
   float sum;

   for (i = 1; i < 5; i++)
      a[i] /= a[0];

   for (i = 1; i < 5; i++) {
      for (j = i; j < 5; j++) {
         sum = 0.0f;
         for (k = 0; k < i; k++)
            sum += a[j * 5 + k] * a[k * 5 + i];
         a[j * 5 + i] -= sum;
      }
      if (i != 5 - 1) {
         for (j = i + 1; j < 5; j++) {
            sum = 0.0f;
            for (k = 0; k < i; k++)
               sum += a[i * 5 + k] * a[k * 5 + j];
            a[i * 5 + j] = (a[i * 5 + j] - sum) / a[i * 5 + i];
         }
      }
   }

   for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++) {
         sum = (float)(i == j);
         for (k = i; k < j; k++)
            sum += a[j * 5 + k] * a[k * 5 + i];
         a[j * 5 + i] = sum;
      }

   for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++) {
         sum = 0.0f;
         for (k = j; k < 5; k++)
            sum += a[i * 5 + k] * a[k * 5 + j];
         a[i * 5 + j] = sum;
      }
}