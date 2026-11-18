char *get_func0_res(double **res, int size)
{
 char str[100];
 strcpy(func0_res, "[");

 int i;
 for (i = 0; i < size; i += 2) {
  double x = atof(res[i]);
  double y = atof(res[i + 1]);

  snprintf(str, 100, "(%.2f, %.2f)", x, y);
  strcat(func0_res, str);

  if (i < size - 2)
   strcat(func0_res, ", ");
 }

 strcat(func0_res, "]");
 return func0_res;
}