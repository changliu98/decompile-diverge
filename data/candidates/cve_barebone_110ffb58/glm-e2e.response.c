void gdImageFillToBorder(gdImage *im, int x, int y, int border, int color) {
    int lastX = -1;
    int restoreAlpha = im->alpha;
    im->alpha = 0;

    // Clamp X coordinate
    if (x >= im->sx) {
        x = im->sx - 1;
    } else if (x < 0) {
        x = 0;
    }

    // Clamp Y coordinate
    if (y >= im->sy) {
        y = im->sy - 1;
    } else if (y < 0) {
        y = 0;
    }

    if (border < 0) {
        im->alpha = restoreAlpha;
        return;
    }

    int i;
    int firstX;
    int lastX2;

    // Scan left
    for (i = x; i >= 0; i--) {
        if (gdImageGetPixel(im, i, y) == border) {
            break;
        }
        gdImageSetPixel(im, i, y, color);
        lastX = i;
    }

    if (lastX == -1) {
        im->alpha = restoreAlpha;
        return;
    }

    firstX = x;

    // Scan right
    for (i = x + 1; i < im->sx; i++) {
        if (gdImageGetPixel(im, i, y) == border) {
            break;
        }
        gdImageSetPixel(im, i, y, color);
        firstX = i;
    }

    // Handle top row
    if (y > 0) {
        int flag = 1;
        for (i = lastX; i <= firstX; i++) {
            int p = gdImageGetPixel(im, i, y - 1);
            if (flag) {
                if (p != border && p != color) {
                    gdImageFillToBorder(im, i, y - 1, border, color);
                    flag = 0;
                }
            } else {
                if (p == border || p == color) {
                    flag = 1;
                }
            }
        }
    }

    // Handle bottom row
    if (y < im->sy - 1) {
        int flag = 1;
        for (i = lastX; i <= firstX; i++) {
            int p = gdImageGetPixel(im, i, y + 1);
            if (flag) {
                if (p != border && p != color) {
                    gdImageFillToBorder(im, i, y + 1, border, color);
                    flag = 0;
                }
            } else {
                if (p == border || p == color) {
                    flag = 1;
                }
            }
        }
    }

    im->alpha = restoreAlpha;
}