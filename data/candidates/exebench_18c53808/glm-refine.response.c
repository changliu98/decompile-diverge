void __cdecl gui_combine_scissor(int *dst, int *src)
{
  if (src)
  {
    // Calculate the intersection of two axis-aligned bounding boxes (scissor rectangles).
    // Rectangles are represented as [x, y, width, height].
    
    int max_x = (dst[0] > src[0]) ? dst[0] : src[0];
    int max_y = (dst[1] > src[1]) ? dst[1] : src[1];
    
    int min_right  = (dst[2] + dst[0] < src[2] + src[0]) ? dst[2] + dst[0] : src[2] + src[0];
    int min_bottom = (dst[3] + dst[1] < src[3] + src[1]) ? dst[3] + dst[1] : src[3] + src[1];

    dst[0] = max_x;
    dst[1] = max_y;
    dst[2] = min_right - max_x;
    dst[3] = min_bottom - max_y;
  }
}