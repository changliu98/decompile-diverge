void parabolic_interpolation
               (float left_val,float middle_val,float right_val,int current_bin,float *result_val,
               int *result_bin)

{
  double dVar1;
  float delta_x;
  int *result_bin_local;
  float *result_val_local;
  int current_bin_local;
  float right_val_local;
  float middle_val_local;
  float left_val_local;
  
  dVar1 = DAT_00102018 *
          (double)((left_val - right_val) / ((left_val - (middle_val + middle_val)) + right_val));
  *result_bin = current_bin + (int)dVar1;
  *result_val = (float)(-(DAT_00102010 * (double)(left_val - right_val)) * (double)(float)dVar1 +
                       (double)middle_val);
  return;
}