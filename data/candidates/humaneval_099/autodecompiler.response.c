int func0(char *str)
{
   double num;
   double temp;

   num = atof(str);
   if(num < 0)
      temp = ceil(num - .5);
   else
      temp = floor(num + .5);

   return((int)temp);
}