gdImagePtr gdImageClone (gdImagePtr im)
{
	int i, j;
	gdImagePtr nim;

	if (im->trueColor) {
		nim = gdImageCreateTrueColor (im->sx, im->sy);
	} else {
		nim = gdImageCreate (im->sx, im->sy);
	}

	if (nim == NULL) {
		return NULL;
	}

	if (im->trueColor) {
		for (i = 0; i < im->sy; i++) {
			for (j = 0; j < im->sx; j++) {
				nim->tpixels[i][j] = im->tpixels[i][j];
			}
		}
	} else {
		nim->colorsTotal = im->colorsTotal;
		for (i = 0; i < 256; i++) {
			nim->red[i] = im->red[i];
			nim->green[i] = im->green[i];
			nim->blue[i] = im->blue[i];
			nim->alpha[i] = im->alpha[i];
			nim->open[i] = im->open[i];
		}
		for (i = 0; i < im->sy; i++) {
			for (j = 0; j < im->sx; j++) {
				nim->pixels[i][j] = im->pixels[i][j];
			}
		}
	}

	if (im->styleLength > 0) {
		nim->styleLength = im->styleLength;
		nim->stylePos = im->stylePos;
		for (i = 0; i < im->styleLength; i++) {
			nim->style[i] = im->style[i];
		}
	}

	nim->interlace = im->interlace;
	nim->alphaBlendingFlag = im->alphaBlendingFlag;
	nim->saveAlphaFlag = im->saveAlphaFlag;
	nim->AA = im->AA;
	nim->AA_color = im->AA_color;
	nim->AA_dont_blend = im->AA_dont_blend;
	nim->cx1 = im->cx1;
	nim->cy1 = im->cy1;
	nim->cx2 = im->cx2;
	nim->cy2 = im->cy2;
	nim->res_x = im->res_x;
	nim->res_y = im->res_y;
	nim->paletteQuantizationMethod = im->paletteQuantizationMethod;
	nim->paletteQuantizationSpeed = im->paletteQuantizationSpeed;
	nim->paletteQuantizationMinQuality = im->paletteQuantizationMinQuality;
	nim->paletteQuantizationMinQuality = im->paletteQuantizationMinQuality;
	nim->interpolation_id = im->interpolation_id;
	nim->interpolation = im->interpolation;

	if (im->brush != NULL) {
		nim->brush = gdImageClone (im->brush);
	}
	if (im->tile != NULL) {
		nim->tile = gdImageClone (im->tile);
	}
	if (im->style != NULL) {
		gdImageSetStyle(nim, im->style, im->styleLength);
	}

	for (i = 0; i < 256; i++) {
		nim->brushColorMap[i] = im->brushColorMap[i];
		nim->tileColorMap[i] = im->tileColorMap[i];
	}

	if (im->polyAllocated > 0) {
		nim->polyAllocated = im->polyAllocated;
		for (i = 0; i < im->polyAllocated; i++) {
			nim->polyInts[i] = im->polyInts[i];
		}
	}

	return nim;
}