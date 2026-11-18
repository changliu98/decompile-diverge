int gen_gf_field(unsigned char gf[], int pp)
{
   int i, j, p;
   int status = 0;

   if ((pp & 0x100) == 0)
   {
      status = -1;
   }
   else
   {
      p = pp & 0xff;

      gf[0] = 0;
      gf[1] = 1;
      j = 1;
      for (i = 2; ; i++)
      {
         if (i < 256)
         {
            j <<= 1;
            if ((j & 0x100) != 0)
            {
               j &= 0xff;
               j ^= p;
            }
            gf[i] = (unsigned char)j;
         }
         else
         {
            break;
         }
      }
   }

   return(status);
}