void gdImageFillToBorder(struct _gdImage *im, int x, int y, int border, int color)
{
  int left; int right;
  int lastleft; int lastright;
  int alphaBlendingFlag;
  int i;
  int c;
  int lastleftborder;
  int lastrightborder;
  int xpos = x;
  int ypos = y;
  if (border < 0)
    return;
  left = -1;
  alphaBlendingFlag = im->alphaBlendingFlag;
  im->alphaBlendingFlag = 0;
  if (xpos >= im->sx)
    xpos = im->sx - 1;
  else if (xpos < 0)
    xpos = 0;
  if (ypos >= im->sy)
    ypos = im->sy - 1;
  else if (ypos < 0)
    ypos = 0;
  for (i = xpos; i >= 0; i--) {
    c = gdimage_getpixel(im, i, ypos);
    if (c == border)
      break;
    gdimage_setpixel(im, i, ypos, color);
    left = i;
  }
  if (left == -1) {
    im->alphaBlendingFlag = alphaBlendingFlag;
    return;
  }
  right = xpos;
  for (i = xpos + 1; i < im->sx; i++) {
    c = gdimage_getpixel(im, i, ypos);
    if (c == border)
      break;
    gdimage_setpixel(im, i, ypos, color);
    right = i;
  }
  if (ypos > 0) {
    lastleftborder = 1;
    for (i = left; i <= right; i++) {
      c = gdimage_getpixel(im, i, ypos - 1);
      if (lastleftborder) {
        if (c != border && c != color) {
          gdImageFillToBorder(im, i, ypos - 1, border, color);
          lastleftborder = 0;
        }
      }
      else {
        if (c == border || c == color)
          lastleftborder = 1;
      }
    }
  }
  if (ypos < im->sy - 1) {
    lastrightborder = 1;
    for (i = left; i <= right; i++) {
      c = gdimage_getpixel(im, i, ypos + 1);
      if (lastrightborder) {
        if (c != border && c != color) {
          gdImageFillToBorder(im, i, ypos + 1, border, color);
          lastrightborder = 0;
        }
      }
      else {
        if (c == border || c == color)
          lastrightborder = 1;
      }
    }
  }
  im->alphaBlendingFlag = alphaBlendingFlag;
}