long argmatch_exact(char *string, char *table[])
{
   long n = 0;
   long answer;

   while (1)
   {
      if (table[n] == NULL)
      {
         answer = -1;
         break;
      }
      if (!strcmp(table[n], string))
      {
         answer = n;
         break;
      }
      n++;
   }
   return(answer);
}