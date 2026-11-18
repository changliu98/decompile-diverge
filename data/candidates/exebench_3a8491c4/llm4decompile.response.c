void Calc_Sum_Mean(double Array[100],double *Sum,double *Mean)
{
  int i;
  *Sum = 0.0;
  for(i=0;i<100;i++)
    *Sum += Array[i];
  *Mean = *Sum / 100.0;
}