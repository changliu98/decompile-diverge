gdImagePtr __cdecl gdImageClone(gdImagePtr src)
{
  int x; // [rsp+0h] [rbp-20h]
  int xa; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]
  int ia; // [rsp+4h] [rbp-1Ch]
  int ib; // [rsp+4h] [rbp-1Ch]
  int ic; // [rsp+4h] [rbp-1Ch]
  int id; // [rsp+4h] [rbp-1Ch]
  int ie; // [rsp+4h] [rbp-1Ch]
  gdImagePtr dst; // [rsp+8h] [rbp-18h]

  if ( src->trueColor )
    dst = gdImageCreateTrueColor(src->sx, src->sy);
  else
    dst = gdImageCreate(src->sx, src->sy);
  if ( !dst )
    return 0LL;
  if ( src->trueColor )
  {
    for ( ib = 0; ib < src->sy; ++ib )
    {
      for ( xa = 0; xa < src->sx; ++xa )
        dst->tpixels[ib][xa] = src->tpixels[ib][xa];
    }
  }
  else
  {
    dst->colorsTotal = src->colorsTotal;
    for ( i = 0; i < 256; ++i )
    {
      dst->red[i] = src->red[i];
      dst->green[i] = src->green[i];
      dst->blue[i] = src->blue[i];
      dst->alpha[i] = src->alpha[i];
      dst->open[i] = src->open[i];
    }
    for ( ia = 0; ia < src->sy; ++ia )
    {
      for ( x = 0; x < src->sx; ++x )
        dst->pixels[ia][x] = src->pixels[ia][x];
    }
  }
  if ( src->styleLength > 0 )
  {
    dst->styleLength = src->styleLength;
    dst->stylePos = src->stylePos;
    for ( ic = 0; ic < src->styleLength; ++ic )
      dst->style[ic] = src->style[ic];
  }
  dst->interlace = src->interlace;
  dst->alphaBlendingFlag = src->alphaBlendingFlag;
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
  dst->paletteQuantizationMethod = src->paletteQuantizationMethod;
  dst->paletteQuantizationSpeed = src->paletteQuantizationSpeed;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
  dst->interpolation_id = src->interpolation_id;
  dst->interpolation = src->interpolation;
  if ( src->brush )
    dst->brush = gdImageClone(src->brush);
  if ( src->tile )
    dst->tile = gdImageClone(src->tile);
  if ( src->style )
    gdImageSetStyle(dst, src->style, src->styleLength);
  for ( id = 0; id < 256; ++id )
  {
    dst->brushColorMap[id] = src->brushColorMap[id];
    dst->tileColorMap[id] = src->tileColorMap[id];
  }
  if ( src->polyAllocated > 0 )
  {
    dst->polyAllocated = src->polyAllocated;
    for ( ie = 0; ie < src->polyAllocated; ++ie )
      dst->polyInts[ie] = src->polyInts[ie];
  }
  return dst;
}