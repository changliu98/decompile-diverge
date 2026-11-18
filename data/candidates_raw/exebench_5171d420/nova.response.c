static int func0(struct fb_var_screeninfo *var,
				struct fb_fix_screeninfo *fix)
{
	int err;

	if (!var->xres ||!var->yres) {
		err = 1;
		goto fail;
	}

	fix->line_length = 1024;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->xpanstep = fix->ypanstep = 0;

	fix->ywrapstep = fix->xpanstep * var->xres
		- (1024 - (var->xres * var->bits_per_pixel) % 1024);
	fix->ywrapstep /= 1024;

	err = 0;
fail:
	return err;
}