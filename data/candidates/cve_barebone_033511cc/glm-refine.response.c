gdImagePtr __cdecl gdImageClone(gdImagePtr src)
{
  int y, x, i;
  gdImagePtr dst;

  // 1. Create the destination image based on color type
  if (src->trueColor)
    dst = gdImageCreateTrueColor(src->sx, src->sy);
  else
    dst = gdImageCreate(src->sx, src->sy);

  if (!dst)
    return NULL;

  // 2. Copy pixel data and palette
  if (src->trueColor)
  {
    for (y = 0; y < src->sy; ++y)
      for (x = 0; x < src->sx; ++x)
        dst->tpixels[y][x] = src->tpixels[y][x];
  }
  else
  {
    dst->colorsTotal = src->colorsTotal;
    for (i = 0; i < 256; ++i)
    {
      dst->red[i]   = src->red[i];
      dst->green[i] = src->green[i];
      dst->blue[i]  = src->blue[i];
      dst->alpha[i] = src->alpha[i];
      dst->open[i]  = src->open[i];
    }
    for (y = 0; y < src->sy; ++y)
      for (x = 0; x < src->sx; ++x)
        dst->pixels[y][x] = src->pixels[y][x];
  }

  // 3. Copy style data
  if (src->styleLength > 0)
  {
    dst->styleLength = src->styleLength;
    dst->stylePos    = src->stylePos;
    for (i = 0; i < src->styleLength; ++i)
      dst->style[i] = src->style[i];
  }

  // 4. Copy various configuration flags and properties
  dst->interlace                   = src->interlace;
  dst->alphaBlendingFlag           = src->alphaBlendingFlag;
  dst->saveAlphaFlag               = src->saveAlphaFlag;
  dst->AA                          = src->AA;
  dst->AA_color                    = src->AA_color;
  dst->AA_dont_blend               = src->AA_dont_blend;
  dst->cx1                         = src->cx1;
  dst->cy1                         = src->cy1;
  dst->cx2                         = src->cx2;
  dst->cy2                         = src->cy2;
  dst->res_x                       = src->res_x;
  dst->res_y                       = src->res_y;
  dst->paletteQuantizationMethod   = src->paletteQuantizationMethod;
  dst->paletteQuantizationSpeed    = src->paletteQuantizationSpeed;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality; // Preserved from original decompilation
  dst->interpolation_id            = src->interpolation_id;
  dst->interpolation               = src->interpolation;

  // 5. Recursively clone sub-images (brush and tile)
  if (src->brush)
    dst->brush = gdImageClone(src->brush);
  if (src->tile)
    dst->tile  = gdImageClone(src->tile);

  // 6. Apply style explicitly via API
  if (src->style)
    gdImageSetStyle(dst, src->style, src->styleLength);

  // 7. Copy color maps
  for (i = 0; i < 256; ++i)
  {
    dst->brushColorMap[i] = src->brushColorMap[i];
    dst->tileColorMap[i]  = src->tileColorMap[i];
  }

  // 8. Copy polygon allocation data
  if (src->polyAllocated > 0)
  {
    dst->polyAllocated = src->polyAllocated;
    for (i = 0; i < src->polyAllocated; ++i)
      dst->polyInts[i] = src->polyInts[i];
  }

  return dst;
}