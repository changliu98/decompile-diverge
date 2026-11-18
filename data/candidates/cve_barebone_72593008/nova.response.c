static int ImagingPcxDecode(struct vc_data *vc, struct fb_info *info,
			  const unsigned short *s, int count)
{
	unsigned short *dest;
	unsigned int c, mask;
	int col, row, rows;

	if (!con_is_visible(vc, info, s, count))
		return 0;

	if (info->var.xoffset >= info->var.xres_virtual) {
		info->var.xoffset = -1;
		col = -1;
	} else {
		unsigned char *p = (unsigned char *)s;
		if (count < 2 || (p[0] & 0xc0)!= 0xc0)
			col = info->var.xoffset;
		else
			col = (info->var.xoffset + p[1] + 255) % info->var.xres_virtual;
	}

	while (info->var.xoffset < info->var.xres_virtual) {
		rows = info->var.yres_virtual / info->var.yres;
		for (row = 1; row <= rows; row++) {
			dest = (unsigned short *)info->screen_base +
				info->fix.line_length / 2 *
				(info->var.yoffset + row * info->var.yres) + col;
			c = s[0];
			mask = s[1];
			do {
				if (mask & 0x08)
					*dest = c;
				dest++;
				mask <<= 1;
			} while (--count);
		}
		info->var.xoffset++;
		col = -1;
	}
	return -1;
}