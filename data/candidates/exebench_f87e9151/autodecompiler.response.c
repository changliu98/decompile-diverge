void NearestNeighbor(
      int *strchr,
      float *array,
      float value,
      int arlength
   ){
      float bestcrit,crit;
      int i;

      crit=array[0]-value;
      bestcrit=crit*crit;
      *strchr=0;
      i=1;
      while(1){
         if(i>=arlength) break;
         crit=array[i]-value;
         crit=crit*crit;

         if(crit<bestcrit){
            bestcrit=crit;
            *strchr=i;
         }
         i++;
      }
   }