void __cdecl image_fit(
        unsigned int source_w,
        unsigned int source_h,
        unsigned int target_w,
        unsigned int target_h,
        unsigned int *end_w,
        unsigned int *end_h,
        char type)
{
  char v7; // al
  float source_r; // [rsp+4h] [rbp-24h]

  source_r = (float)(int)source_h / (float)(int)source_w;
  if ( type < 1 || type > 2 )
  {
    v7 = 2;
    if ( (float)((float)(int)target_h / (float)(int)target_w) > source_r )
      v7 = 1;
    type = v7;
  }
  if ( type == 1 )
  {
    *end_h = (int)(float)((float)(int)target_w * source_r);
    *end_w = target_w;
  }
  else
  {
    *end_w = (int)(float)((float)(int)target_h / source_r);
    *end_h = target_h;
  }
}