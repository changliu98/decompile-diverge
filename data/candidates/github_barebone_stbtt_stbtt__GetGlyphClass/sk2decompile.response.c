static int stbtt_GetGlyphClass(stbtt_uint8 *data, int g) {
  int format = ttUSHORT(data);
  if (format == 1) {
    int start = ttUSHORT(data + 2);
    int count = ttUSHORT(data + 4);
    if (g >= start && g < start + count)
      return ttUSHORT(data + 6 + 2 * (g - start));
    return 0;
  } else if (format == 2) {
    int low = 0, high = ttUSHORT(data + 2) - 1;
    while (low <= high) {
      int mid = (low + high) >> 1;
      int start2 = ttUSHORT(data + 4 + 6 * mid);
      int end2 = ttUSHORT(data + 4 + 6 * mid + 2);
      if (g < start2)
        high = mid - 1;
      else if (g > end2)
        low = mid + 1;
      else
        return ttUSHORT(data + 4 + 6 * mid + 4);
    }
    return 0;
  }
  return -1;
}