gdImage *gdImageClone(gdImage *src) {
    gdImage *dst;
    int i, j;

    // 0x1c50 is the 'trueColor' flag
    if (src->trueColor) {
        dst = gdImageCreateTrueColor(src->sx, src->sy);
    } else {
        dst = gdImageCreate(src->sx, src->sy);
    }

    if (dst == NULL) {
        return NULL;
    }

    if (!src->trueColor) {
        dst->colorsTotal = src->colorsTotal;
        
        // Copy palette entries (256 iterations)
        for (i = 0; i < 256; i++) {
            dst->red[i] = src->red[i];
            dst->green[i] = src->green[i];
            dst->blue[i] = src->blue[i];
            dst->alpha[i] = src->alpha[i];
            dst->open[i] = src->open[i];
        }

        // Copy pixel data
        for (j = 0; j < src->sy; j++) {
            for (i = 0; i < src->sx; i++) {
                dst->pixels[j][i] = src->pixels[j][i];
            }
        }
    } else {
        // Copy truecolor pixel data (tpixels)
        for (j = 0; j < src->sy; j++) {
            for (i = 0; i < src->sx; i++) {
                dst->tpixels[j][i] = src->tpixels[j][i];
            }
        }
    }

    // Copy style information
    if (src->styleLength > 0) {
        dst->styleLength = src->styleLength;
        dst->stylePos = src->stylePos;
        for (i = 0; i < src->styleLength; i++) {
            dst->style[i] = src->style[i];
        }
    }

    // Copy brush and tile images recursively
    if (src->brush != NULL) {
        dst->brush = gdImageClone(src->brush);
    }
    if (src->tile != NULL) {
        dst->tile = gdImageClone(src->tile);
    }

    // Copy style array using library function if it exists
    if (src->style != NULL) {
        gdImageSetStyle(dst, src->style, src->styleLength);
    }

    // Copy interlace and transparency settings
    for (i = 0; i < 256; i++) {
        dst->brushColorMap[i] = src->brushColorMap[i];
        dst->tileColorMap[i] = src->tileColorMap[i];
    }

    if (src->transparent > 0) {
        dst->transparent = src->transparent;
        for (i = 0; i < src->transparent; i++) {
            dst->polyInts[i] = src->polyInts[i];
        }
    }

    // Copy remaining miscellaneous properties
    dst->polyAllocated = src->polyAllocated;
    dst->thick = src->thick;
    dst->alphaBlendingFlag = src->alphaBlendingFlag;
    dst->antialias = src->antialias;
    dst->interlace = src->interlace;
    dst->trueColor = src->trueColor;
    dst->saveAlphaFlag = src->saveAlphaFlag;
    dst->AA = src->AA;
    dst->AA_color = src->AA_color;
    dst->AA_dont_blend = src->AA_dont_blend;
    dst->cx1 = src->cx1;
    dst->cy1 = src->cy1;
    dst->cx2 = src->cx2;
    dst->cy2 = src->cy2;
    dst->res_x = src->res_x;
    dst->res_y = src->res_y;

    return dst;
}