int stbi__bmp_set_mask_defaults( FB_GFXCTX *context, int depth )
{
 int ret;

 if (depth == 3) {

  ret = 1;

 } else if (depth == 0) {





  if (context->bpp == 16) {
   context->red_mask = 0x7c00;
   context->green_mask = 0x03e0;
   context->blue_mask = 0x001f;
  } else if (context->bpp == 32) {
   context->red_mask = 0x00ff0000;
   context->green_mask = 0x0000ff00;
   context->blue_mask = 0x000000ff;
   context->alpha_mask = 0xff000000;
   context->color_mask = 0x00000000;
  } else {
   context->alpha_mask = 0x00000000;
   context->blue_mask = 0x00000000;
   context->green_mask = 0x00000000;
   context->red_mask = 0x00000000;
  }

  ret = 1;

 } else {

  ret = 0;

 }

 return ret;
}