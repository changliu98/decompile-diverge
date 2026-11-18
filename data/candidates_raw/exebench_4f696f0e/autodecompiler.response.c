void swap_4 (void * s)
{
   char c;
   c = *((char *) s + 0);
   *((char *) s + 0) = *((char *) s + 3);
   *((char *) s + 3) = c;
   c = *((char *) s + 1);
   *((char *) s + 1) = *((char *) s + 2);
   *((char *) s + 2) = c;
}