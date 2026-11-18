gdImagePtr gdImageCreateFromTgaCtx (gdIOCtx * ctx)
{
	int x, y;
	int index;
	int bitmap_caret = 0;
	gdImagePtr im;
	oTga *tga;
	int *tpix;
	int res;

	tga = (oTga *)gdMalloc(sizeof(oTga));
	if (tga == NULL) {
		return NULL;
	}
	tga->bitmap = NULL;
	tga->ident = NULL;

	res = read_header_tga(ctx, tga);
	if (res < 0) {
		free_tga(tga);
		return NULL;
	}

	res = read_image_tga(ctx, tga);
	if (res < 0) {
		free_tga(tga);
		return NULL;
	}

	im = gdImageCreateTrueColor(tga->width, tga->height);
	if (im == NULL) {
		free_tga(tga);
		return NULL;
	}

	if (tga->alphabits != 0) {
		gdImageAlphaBlending(im, 0);
		gdImageSaveAlpha(im, 1);
	}

	for (y = 0; y < tga->height; y++) {
		tpix = (int *) im->tpixels[y];
		for (x = 0; x < tga->width; x++) {
			if (tga->bits == 24) {
				index = (tga->bitmap[bitmap_caret+2]<<16) + (tga->bitmap[bitmap_caret+1]<<8) + tga->bitmap[bitmap_caret];
				bitmap_caret += 3;
			} else if (tga->bits == 32 || tga->alphabits != 0) {
				index = (tga->bitmap[bitmap_caret+3]>>1)<<24;
				index += (tga->bitmap[bitmap_caret+2]<<16) + (tga->bitmap[bitmap_caret+1]<<8) + tga->bitmap[bitmap_caret];
				bitmap_caret += 4;
			}
			*tpix++ = index;
		}
	}

	if (tga->flipv && tga->fliph) {
		gdImageFlipBoth(im);
	} else if (tga->flipv) {
		gdImageFlipVertical(im);
	} else if (tga->fliph) {
		gdImageFlipHorizontal(im);
	}

	free_tga(tga);

	return im;
}