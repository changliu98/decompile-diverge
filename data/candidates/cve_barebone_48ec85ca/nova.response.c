static void initialise_banding(struct vc_data *vc, struct fb_info *info, int color)
{
	unsigned long h, w, x, y;
	unsigned long hw = info->var.xres * info->var.bits_per_pixel / 8;
	unsigned long fg, bg;
	unsigned long *p;

	info->fbops->fb_fillrect(info, &(info->var.green));

	while (1) {
		switch (color) {
		case 1:
			info->fbops->fb_fillrect(info, &(info->var.red));
			info->fbops->fb_fillrect(info, &(info->var.blue));
			break;
		case 2:
			info->fbops->fb_fillrect(info, &(info->var.green));
			info->fbops->fb_fillrect(info, &(info->var.blue));
			break;
		case 3:
			info->fbops->fb_fillrect(info, &(info->var.green));
			info->fbops->fb_fillrect(info, &(info->var.red));
			break;
		case 4:
			info->fbops->fb_fillrect(info, &(info->var.blue));
			info->fbops->fb_fillrect(info, &(info->var.red));
			break;
		case 5:
			info->fbops->fb_fillrect(info, &(info->var.blue));
			info->fbops->fb_fillrect(info, &(info->var.green));
			break;
		case 6:
			info->fbops->fb_fillrect(info, &(info->var.red));
			info->fbops->fb_fillrect(info, &(info->var.green));
			break;
		}

		info->fbops->