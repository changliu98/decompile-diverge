float binary_search(float value,float *array,int size)

{
  int iVar1;
  float fVar2;
  float x;
  int mid;
  int high;
  int low;
  int size_local;
  float *array_local;
  float value_local;
  float local_c;
  
  if ((value != *array) || (NAN(value) || NAN(*array))) {
    if (*array <= value) {
      if (value < array[size + -1] || value == array[size + -1]) {
        if ((value != array[size + -1]) || (NAN(value) || NAN(array[size + -1]))) {
          low = 0;
          high = size + -1;
          while (low <= high) {
            iVar1 = (low + high) / 2;
            if (array[iVar1] <= value) {
              if (value < array[iVar1] || value == array[iVar1]) {
                return (float)iVar1;
              }
              low = iVar1 + 1;
            }
            else {
              high = iVar1 + -1;
            }
          }
          fVar2 = (value - array[high]) / (array[low] - array[high]);
          local_c = (float)((double)high * (DAT_00102010 - (double)fVar2) +
                           (double)((float)low * fVar2));
        }
        else {
          local_c = (float)(size + -1);
        }
      }
      else {
        local_c = DAT_00102028;
      }
    }
    else {
      local_c = DAT_00102028;
    }
  }
  else {
    local_c = 0.0;
  }
  return local_c;
}