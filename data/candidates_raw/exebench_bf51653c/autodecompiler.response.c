void g729a_Pre_Process(int pitch_gain, int *gains, int *old_gains)
{
   int i;
   if (pitch_gain==0)
   {
      for (i=0;i<7;i++)
         old_gains[i] = (int)((255*(long)old_gains[i])>>8);
   }
   else
   {
      for (i=0;i<7;i++)
      {
         int temp;
         int temp2;
         if (pitch_gain*(long)gains[i]>=0)
            temp=128;
         else
            temp=-128;
         temp2=(int)((255*(long)old_gains[i])>>8);
         old_gains[i]=temp+temp2;
      }
   }
   gains[5]=gains[4];
   gains[4]=gains[3];
   gains[3]=gains[2];
   gains[1]=gains[0];
   gains[0]=pitch_gain;
}