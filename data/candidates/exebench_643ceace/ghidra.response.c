void image_fit(uint source_w,uint source_h,uint target_w,uint target_h,uint *end_w,uint *end_h,
              char type)

{
  float fVar1;
  float target_r;
  float source_r;
  uint *end_h_local;
  uint *end_w_local;
  uint target_h_local;
  uint target_w_local;
  uint source_h_local;
  uint source_w_local;
  
  fVar1 = (float)source_h / (float)source_w;
  if (((type < '\x01') || ('\x02' < type)) &&
     (type = '\x02', fVar1 < (float)target_h / (float)target_w)) {
    type = '\x01';
  }
  if (type == '\x01') {
    *end_h = (uint)(long)((float)target_w * fVar1);
    *end_w = target_w;
  }
  else {
    *end_w = (uint)(long)((float)target_h / fVar1);
    *end_h = target_h;
  }
  return;
}