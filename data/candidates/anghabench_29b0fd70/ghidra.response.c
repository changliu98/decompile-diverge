float map(int x,int in_min,int in_max,float out_min,float out_max)

{
  double output;
  double slope;
  float out_max_local;
  float out_min_local;
  int in_max_local;
  int in_min_local;
  int x_local;
  
  return (float)(((DAT_00102008 * (double)(out_max - out_min)) / (double)(in_max - in_min)) *
                 (double)(x - in_min) + (double)out_min);
}