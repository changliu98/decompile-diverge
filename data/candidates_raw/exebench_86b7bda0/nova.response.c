static void func0(struct drm_display_mode *mode)
{
	u32 a, b, c, d;

	a = mode->crtc_hdisplay * 16;
	b = mode->crtc_hblank_start * 16;
	c = mode->crtc_hblank_end * 16;
	d = mode->crtc_hdisplay * 16;

	while (1) {
		u32 e, f, g, h;

		e = a - b;
		f = c - b;
		g = d - c;
		h = d - a;

		if (e < 128 || f < 128 || g < 128 || h < 128) {
			a *= 2;
			b *= 2;
			c *= 2;
			d *= 2;
		} else {
			u32 avg = (e + f + g + h) / 4;

			e = (e * 565 + avg / 2) / avg;
			f = (f * 565 + avg / 2) / avg;
			g = (g * 565 + avg / 2) / avg;
			h = (h * 565 + avg / 2) / avg;

			a = (e + 128) >> 8;
			b = (f + 128) >> 8;
			c = (g + 128) >> 8;
			d = (h + 128) >> 8;
			break;
		}
	}

	mode->htotal = a;
	mode->hsync_end = b;
	mode->hsync_start = c;
	mode->hts = d;
}