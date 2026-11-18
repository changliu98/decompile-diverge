char *func0(char *argv[], int argc)
{
 int i;
 char delim[] = "-";

 strcpy(func0_res, "usage: %s <seed> [dump]\n");
 for (i = 0; ; i++) {
  if (i >= argc)
   break;

  strcat(func0_res, argv[i]);
  if (i < argc-1)
   strcat(func0_res, delim);
 }

 return func0_res;
}