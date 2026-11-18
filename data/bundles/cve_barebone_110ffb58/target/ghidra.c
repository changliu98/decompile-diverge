/* WARNING: Enum "gdInterpolationMethod": Some values do not have unique names */

void gdImageFillToBorder(gdImagePtr im,int x,int y,int border,int color)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int c_1;
  int c;
  int restoreAlphaBleding;
  int i;
  int rightLimit;
  int leftLimit;
  int lastBorder;
  int color_local;
  int border_local;
  int y_local;
  int x_local;
  gdImagePtr im_local;
  
  if (-1 < border) {
    leftLimit = -1;
    iVar1 = im->alphaBlendingFlag;
    im->alphaBlendingFlag = 0;
    if (x < im->sx) {
      x_local = x;
      if (x < 0) {
        x_local = 0;
      }
    }
    else {
      x_local = im->sx + -1;
    }
    if (y < im->sy) {
      y_local = y;
      if (y < 0) {
        y_local = 0;
      }
    }
    else {
      y_local = im->sy + -1;
    }
    i = x_local;
    while ((-1 < i && (iVar3 = gdImageGetPixel(im,i,y_local), iVar3 != border))) {
      gdImageSetPixel(im,i,y_local,color);
      leftLimit = i;
      i = i + -1;
    }
    if (leftLimit == -1) {
      im->alphaBlendingFlag = iVar1;
    }
    else {
      while ((i = x_local + 1, i < im->sx &&
             (iVar3 = gdImageGetPixel(im,i,y_local), iVar3 != border))) {
        gdImageSetPixel(im,i,y_local,color);
        x_local = i;
      }
      if (0 < y_local) {
        bVar2 = true;
        for (i = leftLimit; i <= x_local; i = i + 1) {
          iVar3 = gdImageGetPixel(im,i,y_local + -1);
          if (bVar2) {
            if ((iVar3 != border) && (iVar3 != color)) {
              gdImageFillToBorder(im,i,y_local + -1,border,color);
              bVar2 = false;
            }
          }
          else if ((iVar3 == border) || (iVar3 == color)) {
            bVar2 = true;
          }
        }
      }
      if (y_local < im->sy + -1) {
        bVar2 = true;
        for (i = leftLimit; i <= x_local; i = i + 1) {
          iVar3 = gdImageGetPixel(im,i,y_local + 1);
          if (bVar2) {
            if ((iVar3 != border) && (iVar3 != color)) {
              gdImageFillToBorder(im,i,y_local + 1,border,color);
              bVar2 = false;
            }
          }
          else if ((iVar3 == border) || (iVar3 == color)) {
            bVar2 = true;
          }
        }
      }
      im->alphaBlendingFlag = iVar1;
    }
  }
  return;
}