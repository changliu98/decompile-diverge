int func0(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int err = 0;

	switch (var->bits_per_pixel) {
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 24:
	case 32:
		break;
	default:
		return -EINVAL;
	}

	err = set_depth(var, var->bits_per_pixel);
	if (err) {
		int err2 = set_depth(var, info->var.bits_per_pixel);
		if (err2)
			return err2;
	}

	var->red.offset = 0;
	var->green.offset = var->bits_per_pixel == 16? 5 : 0;
	var->blue.offset = var->bits_per_pixel == 16? 10 : 10;

	return err;
}