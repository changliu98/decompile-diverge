static void scale_mat(struct fb_var_screeninfo *var,
				int xres, int yres)
{
	if (xres!= 1024) {
		var->xres_virtual = var->xres_virtual * xres / 1024;
		var->xres = var->xres * xres / 1024;
		var->yres_virtual = var->yres_virtual * xres / 1024;
	}
	if (yres!= 1024) {
		var->yres_virtual = var->yres_virtual * yres / 1024;
		var->yres = var->yres * yres / 1024;
		var->xres_virtual = var->xres_virtual * yres / 1024;
	}
}