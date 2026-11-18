void gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color) {
  int x1, i, x2, c, start, saveAlphaBlendingFlag;
  if (border < 0) {
    return;
  }
  x1 = -1;
  saveAlphaBlendingFlag = im->alphaBlendingFlag;
  im->alphaBlendingFlag = 0;
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
  for (i = x; i >= 0; i--) {
    if (gdImageGetPixel(im, i, y) == border) {
      break;
    }
    gdImageSetPixel(im, i, y, color);
    x1 = i;
  }
  if (x1 == -1) {
    im->alphaBlendingFlag = saveAlphaBlendingFlag;
    return;
  }
  x2 = x;
  for (i = x + 1; i < im->sx; i++) {
    if (gdImageGetPixel(im, i, y) == border) {
      break;
    }
    gdImageSetPixel(im, i, y, color);
    x2 = i;
  }
  if (y > 0) {
    start = 1;
    for (i = x1; i <= x2; i++) {
      c = gdImageGetPixel(im, i, y - 1);
      if (start) {
        if (c != border && c != color) {
          gdImageFillToBorder(im, i, y - 1, border, color);
          start = 0;
        }
      } else {
        if (c == border || c == color) {
          start = 1;
        }
      }
    }
  }
  if (y < im->sy - 1) {
    start = 1;
    for (i = x1; i <= x2; i++) {
      c = gdImageGetPixel(im, i, y + 1);
      if (start) {
        if (c != border && c != color) {
          gdImageFillToBorder(im, i, y + 1, border, color);
          start = 0;
        }
      } else {
        if (c == border || c == color) {
          start = 1;
        }
      }
    }
  }
  im->alphaBlendingFlag = saveAlphaBlendingFlag;
}