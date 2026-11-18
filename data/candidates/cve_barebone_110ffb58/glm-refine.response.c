void __cdecl gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color)
{
  int px, py;
  int leftLimit, rightLimit;
  int restoreAlphaBlending;
  int i, c;
  int lastBorder;

  // If the border color is invalid, do nothing
  if (border < 0)
    return;

  // Clamp starting coordinates within image bounds
  px = (x < 0) ? 0 : (x >= im->sx ? im->sx - 1 : x);
  py = (y < 0) ? 0 : (y >= im->sy ? im->sy - 1 : y);

  leftLimit = -1;
  restoreAlphaBlending = im->alphaBlendingFlag;
  im->alphaBlendingFlag = 0;

  // 1. Fill leftwards from the starting point
  for (i = px; i >= 0 && gdImageGetPixel(im, i, py) != border; --i)
  {
    gdImageSetPixel(im, i, py, color);
    leftLimit = i;
  }

  // If the starting pixel itself was a border, leftLimit remains -1
  if (leftLimit == -1)
  {
    im->alphaBlendingFlag = restoreAlphaBlending;
    return;
  }

  // 2. Fill rightwards from the starting point
  rightLimit = px;
  for (i = px + 1; i < im->sx && gdImageGetPixel(im, i, py) != border; ++i)
  {
    gdImageSetPixel(im, i, py, color);
    rightLimit = i;
  }

  // 3. Scan the row above and recursively fill connected regions
  if (py > 0)
  {
    lastBorder = 1;
    for (i = leftLimit; i <= rightLimit; ++i)
    {
      c = gdImageGetPixel(im, i, py - 1);
      if (lastBorder)
      {
        if (c != border && c != color)
        {
          gdImageFillToBorder(im, i, py - 1, border, color);
          lastBorder = 0;
        }
      }
      else if (c == border || c == color)
      {
        lastBorder = 1;
      }
    }
  }

  // 4. Scan the row below and recursively fill connected regions
  if (py < im->sy - 1)
  {
    lastBorder = 1;
    for (i = leftLimit; i <= rightLimit; ++i)
    {
      c = gdImageGetPixel(im, i, py + 1);
      if (lastBorder)
      {
        if (c != border && c != color)
        {
          gdImageFillToBorder(im, i, py + 1, border, color);
          lastBorder = 0;
        }
      }
      else if (c == border || c == color)
      {
        lastBorder = 1;
      }
    }
  }

  // Restore the original alpha blending flag
  im->alphaBlendingFlag = restoreAlphaBlending;
}