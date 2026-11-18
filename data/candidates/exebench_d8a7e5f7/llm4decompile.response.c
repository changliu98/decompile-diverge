int ExtractRnick(char *Rnick, char *incoming_msg)
{
   int i=0, j=0;

   if (*incoming_msg == ':')
     incoming_msg++;

   while ((*incoming_msg != '!') && (*incoming_msg != '\0'))
     {
       Rnick[i] = *incoming_msg;
       incoming_msg++;
       i++;
     }
   Rnick[i] = '\0';

   if ((Rnick[0] > '/') && (Rnick[0] < 123))
     return 1;
   else
     return 0;
}