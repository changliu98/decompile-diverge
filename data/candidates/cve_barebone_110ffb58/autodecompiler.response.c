void gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color)
{
 int lastLeft, left, right, oldColor, lastRight;
 int p;
 int alphaBlending;

 if (border < 0) {
  return;
 }

 lastLeft = -1;

 alphaBlending = im->alphaBlendingFlag;
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


 p = x;
 while ((p >= 0) && (gdImageGetPixel(im, p, y) != border)) {
  gdImageSetPixel(im, p, y, color);
  lastLeft = p;
  --p;
 }
 if (lastLeft == -1) {
  im->alphaBlendingFlag = alphaBlending;
  return;
 }
 right = x;
 p = x + 1;
 while ((p < im->sx) && (gdImageGetPixel(im, p, y) != border)) {
  gdImageSetPixel(im, p, y, color);
  right = p;
  ++p;
 }

 if (y > 0) {
  lastRight = -1;
  lastLeft = lastLeft - 1;
  p = lastLeft;
  while ((p <= right) && (p >= 0)) {
   oldColor = gdImageGetPixel(im, p, y - 1);
   if (lastRight == 0) {
    if ((oldColor == border) || (oldColor == color)) {
     lastRight = 1;
    }
   } else if ((oldColor != border) && (oldColor != color)) {
    gdImageFillToBorder(im, p, y - 1, border, color);
    lastRight = 0;
   }
   ++p;
  }
 }

 if (y < (im->sy - 1)) {
  lastRight = -1;
  lastLeft = lastLeft - 1;
  p = lastLeft;
  while ((p <= right) && (p >= 0)) {
   oldColor = gdImageGetPixel(im, p, y + 1);
   if (lastRight == 0) {
    if ((oldColor == border) || (oldColor == color)) {
     lastRight = 1;
    }
   } else if ((oldColor != border) && (oldColor != color)) {
    gdImageFillToBorder(im, p, y + 1, border, color);
    lastRight = 0;
   }
   ++p;
  }
 }
 im->alphaBlendingFlag = alphaBlending;
}