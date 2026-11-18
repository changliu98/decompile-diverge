static int func0(u8 *buf, int x, int y, int w, int h, int stride,
		     int bpp)
{
	if (w) {
		if (y) {
			memcpy(&buf[x * 7 + (y + 1) * stride / 2],
			       &buf[x * 7 + (y - 1) * stride / 2],
			       w / 2, h / 2, stride, bpp);
		}
		memcpy(&buf[x * 7 + y * stride / 2],
		       &buf[x * 7 + y * stride / 2],
		       w / 2, h, stride, bpp);
	} else {
		if (y)
			memcpy(&buf[x * 7 + y * stride / 2],
			       &buf[x * 7 + (y - 1) * stride / 2],
			       h, stride, 0);
	}
	return x + w;
}