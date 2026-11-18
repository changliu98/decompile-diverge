static void image_fit(
  unsigned int source_w, unsigned int source_h,
  unsigned int target_w, unsigned int target_h,
  unsigned int *end_w, unsigned int *end_h,char type)
{
  float source_r, target_r;

  source_r=(float) source_h / (float) source_w;
  target_r=(float) target_h / (float) target_w;

  if(type < 1 || type > 2)
    type=(target_r > source_r) ? 1 : 2;






  if(type == 1)
  {
    *end_h=target_w*source_r;
    *end_w=target_w;
  }
  else
  {
    *end_w=target_h/source_r;
    *end_h=target_h;
  }
}