static int stbtt_GetCoverageIndex(stbtt_uint8 *glyph, int pt) {
  int format = ttUSHORT(glyph);
  if (format == 1) {
    int lo = 0, hi = ttUSHORT(glyph + 2) - 1;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      int pt1 = ttUSHORT(glyph + 4 + 2 * mid);
      if (pt < pt1)
        hi = mid - 1;
      else if (pt > pt1)
        lo = mid + 1;
      else
        return mid;
    }
    return -1;
  } else if (format == 2) {
    int lo = 0, hi = ttUSHORT(glyph + 2) - 1;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      int pt1 = ttUSHORT(glyph + 4 + 6 * mid);
      int pt2 = ttUSHORT(glyph + 4 + 6 * mid + 2);
      if (pt < pt1)
        hi = mid - 1;
      else if (pt > pt2)
        lo = mid + 1;
      else
        return pt + ttUSHORT(glyph + 4 + 6 * mid + 4) - pt1;
    }
    return -1;
  } else
    return -1;
}