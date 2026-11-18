#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>

void P_stats(float *prcp,int *rain_hrs, int *conseq_hrs,int *st_hr,
        float *max_p,int *max_hr, int mo, int *pflag)
{
# 215 "make_lookup_table.c"
  int i;
  int tmp_hrs=0;

  *rain_hrs=0;
  *max_hr=0;
  *max_p=0;
  *conseq_hrs=0;
  *st_hr=0;


  for(i=0;i<24;i++){
    if(prcp[i]>0.0){
      *rain_hrs+=1;
      if(prcp[i]>(*max_p)){
 *max_p=prcp[i];
 *max_hr=i;
      }
    }
  }


  for(i=0;i<24;i++){
    pflag[i]=0;
    if(prcp[i]>0.0){
      tmp_hrs+=1;
      pflag[i]=1;
    }
    else if(tmp_hrs>*conseq_hrs){
      *conseq_hrs=tmp_hrs;
      *st_hr=i-*conseq_hrs;
      tmp_hrs=0;
    }
  }


  if(tmp_hrs>*conseq_hrs){
    *conseq_hrs=tmp_hrs;
    *st_hr=i-*conseq_hrs;
  }
}
