void
process_bitmap_updates(STREAM s)
{
	uint16 num_updates;
	uint16 left, top, right, bottom, width, height, cx, cy, bpp, compress, size;
	uint16 x, y, w, h, Bpp;
	uint8 *bmpdata, *data;
	uint8 *output;
	STREAM ss;

	logger(Protocol, Debug, "%s()", "process_bitmap_updates");
	{ (num_updates) = *((uint16*)((s)->p)); (s)->p += 2; };
	for (x = 0; x < num_updates; x++)
	{
		{ (left) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (top) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (right) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (bottom) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (width) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (height) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (bpp) = *((uint16*)((s)->p)); (s)->p += 2; };
		Bpp = (bpp + 7) / 8;
		{ (compress) = *((uint16*)((s)->p)); (s)->p += 2; };
		{ (size) = *((uint16*)((s)->p)); (s)->p += 2; };
		w = right - left + 1;
		h = bottom - top + 1;
		logger(Graphics, Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
		       left, top, right, bottom, width, height, Bpp, compress);
		if (compress)
		{
			if (!(compress & 0x0400))
			{
				{ (size) = *((uint16*)((s)->p)); (s)->p += 2; };
				{ (s)->p += (4); };
			}
			data = s->p;
			s->p += size;
			output = xmalloc(width * height * Bpp);
			if (bitmap_decompress(output, width, height, data, size, Bpp))
			{
				ui_paint_bitmap(left, top, w, h, width, height, output);
			}
			else
			{
				logger(Graphics, Warning, "process_bitmap_updates(), failed to decompress bitmap");
			}
			xfree(output);
		}
		else
		{
			output = xmalloc(width * height * Bpp);
			for (y = 0; y < height; y++)
			{
				memcpy(output + ((height - y - 1) * width * Bpp), s->p, width * Bpp);
				s->p += width * Bpp;
			}
			ui_paint_bitmap(left, top, w, h, width, height, output);
			xfree(output);
		}
	}
}