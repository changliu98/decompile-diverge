gdImagePtr gdImageClone(gdImagePtr im)
{
 int x, y;
 gdImagePtr n;
 if (im->trueColor) {
  n = gdImageCreateTrueColor(im->sx, im->sy);
 } else {
  n = gdImageCreate(im->sx, im->sy);
 }
 if (!n) {
  return NULL;
 }
 if (!im->trueColor) {
  n->colorsTotal = im->colorsTotal;
  for (x = 0; x < 256; x++) {
   n->red[x] = im->red[x];
   n->green[x] = im->green[x];
   n->blue[x] = im->blue[x];
   n->alpha[x] = im->alpha[x];
   n->open[x] = im->open[x];
  }
  for (y = 0; y < im->sy; y++) {
   for (x = 0; x < im->sx; x++) {
    n->pixels[y][x] = im->pixels[y][x];
   }
  }
 } else {
  for (y = 0; y < im->sy; y++) {
   for (x = 0; x < im->sx; x++) {
    n->tpixels[y][x] = im->tpixels[y][x];
   }
  }
 }
 if (im->interlace > 0) {
  n->interlace = im->interlace;
 }
 n->transparent = im->transparent;
 n->interpolated = im->interpolated;
 n->AA = im->AA;
 n->AAColor = im->AAColor;
 n->AAtransparent = im->AAtransparent;
 n->tileColor = im->tileColor;
 n->tile = im->tile;
 n->brush = im->brush;
 n->styleLength = im->styleLength;
 n->styleStep = im->styleStep;
 n->stylePos = im->stylePos;
 n->style = im->style;
 n->style = im->style;
 n->styleStep = im->styleStep;
 n->stylePos = im->stylePos;
 n->style = im->style;
 n->style = im->style;
 n->styleStep = im->styleStep;
 n->stylePos = im->stylePos;
 n->style = im->style;
 n->style = im->style;
 n->styleStep = im->styleStep;
 n->stylePos = im->stylePos;
 n->style = im->style;
 if (im->tileColorMap) {
  n->tileColorMap = gdImageClone(im->tileColorMap);
 }
 if (im->brushColorMap) {
  n->brushColorMap = gdImageClone(im->brushColorMap);
 }
 if (im->style) {
  gdImageSetStyle(n, im->style, im->styleLength);
 }
 for (x = 0; x < 256; x++) {
  n->color[x] = im->color[x];
  n->tileColor[x] = im->tileColor[x];
 }
 if (im->colorsTotal > 0) {
  n->colorsTotal = im->colorsTotal;
  for (x = 0; x < im->colorsTotal; x++) {
   n->colors[x] = im->colors[x];
  }
 }
 return n;
}