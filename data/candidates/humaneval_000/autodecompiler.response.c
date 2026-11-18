int func0(float *data, int length, float threshold)
{
 int i, j;
 int ret;

 for (i = 0; i < length; i++) {
  for (j = i + 1; j < length; j++) {
   if (fabsf(data[i] - data[j]) < threshold) {
    ret = 1;
    goto out;
   }
  }
 }

out:
 return ret;
}