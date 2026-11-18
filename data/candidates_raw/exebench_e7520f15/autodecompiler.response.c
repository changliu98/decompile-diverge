int

rowcol_to_dtmx (int row, int col, long *mx, int *r)






{
   int status;
   int c;

   if ((row < 0 || row > 83) || (col < 0 || col > 47))
   {
      status = (-1);
   }
   else
   {
      if (!mx || !r)
      {
         status = (-1);
      }
      else
      {
         c = row + (col / 8) * 84;
         *mx = c;
         *r = col % 8;
         status = 0;
      }
   }

   return (status);
}