void Calc_Sum_Mean(double *Array,double *Sum,double *Mean)

{
  int i;
  double *Mean_local;
  double *Sum_local;
  double *Array_local;
  
  *Sum = 0.0;
  for (i = 0; i < 100; i = i + 1) {
    *Sum = Array[i] + *Sum;
  }
  *Mean = *Sum / DAT_00102008;
  return;
}