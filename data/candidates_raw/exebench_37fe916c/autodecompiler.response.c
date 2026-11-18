int cfcopyfile(char *source, char *dest, int *status)
{
   if(source != NULL) {
      dest = source;
      rwmode = 1;
   }
   *status = 1;
   return(0);
}