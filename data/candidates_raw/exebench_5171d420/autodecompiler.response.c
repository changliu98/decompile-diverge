int
main(int argc, char **argv)
{
 struct fb_info *info;
 struct hv_size *hv;
 int ret;

 if (!info->var.xres || !info->var.yres) {
  ret = 1;
 } else {
  hv->width = 0;
  hv->height = 0x100000 / info->var.yres;
  hv->xres = 0x100000 / info->var.xres;
  hv->yres = 0;
  hv->x = (0 - (info->var.left_margin * hv->xres)) / 1024;
  hv->y = (0 - (info->var.upper_margin * hv->height)) / 1024;
  ret = 0;
 }

 return ret;
}