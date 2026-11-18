void gdImageFillToBorder (gdImagePtr im, int x, int y, int border, int color)
{
	int alphaBlendingTmp, left, right, i, c;

	if (border < 0) {
		return;
	}

	/* Turn off alpha blending */
	alphaBlendingTmp = im->alphaBlendingFlag;
	im->alphaBlendingFlag = 0;

	/* Make sure we are in the picture */
	if (x >= im->sx) {
		x = im->sx - 1;
	} else if (x < 0) {
		x = 0;
	}
	if (y >= im->sy) {
		y = im->sy - 1;
	} else if (y < 0) {
		y = 0;
	}

	/* Find the left and right borders */
	left = -1;
	for (i = x; (i >= 0) && (gdImageGetPixel(im, i, y) != border); i--) {
		gdImageSetPixel(im, i, y, color);
		left = i;
	}
	if (left == -1) {
		/* Turn alpha blending back on */
		im->alphaBlendingFlag = alphaBlendingTmp;
		return;
	}
	for (right = x + 1; (right < im->sx) && (gdImageGetPixel(im, right, y) != border); right++) {
		gdImageSetPixel(im, right, y, color);
	}

	/* Do the recursive magic */
	if (y > 0) {
		int in_block = 1;
		for (i = left; i <= right; i++) {
			c = gdImageGetPixel(im, i, y - 1);
			if (in_block) {
				if ((c != border) && (c != color)) {
					gdImageFillToBorder(im, i, y - 1, border, color);
					in_block = 0;
				}
			} else {
				if ((c == border) || (c == color)) {
					in_block = 1;
				}
			}
		}
	}
	if (y < im->sy - 1) {
		int in_block = 1;
		for (i = left; i <= right; i++) {
			c = gdImageGetPixel(im, i, y + 1);
			if (in_block) {
				if ((c != border) && (c != color)) {
					gdImageFillToBorder(im, i, y + 1, border, color);
					in_block = 0;
				}
			} else {
				if ((c == border) || (c == color)) {
					in_block = 1;
				}
			}
		}
	}

	/* Turn alpha blending back on */
	im->alphaBlendingFlag = alphaBlendingTmp;
}