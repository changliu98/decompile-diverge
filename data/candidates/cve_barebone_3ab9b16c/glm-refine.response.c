void __cdecl sycc420_to_rgb(opj_image_t *img)
{
  unsigned int i, j;
  int upb, offset;
  unsigned int maxw, maxh;
  int *y, *cb, *cr;
  int *r, *g, *b;
  int *d0, *d1, *d2;

  upb = (1 << img->comps[0].prec) - 1;
  offset = 1 << (img->comps[0].prec - 1);
  
  maxw = img->comps[0].w;
  maxh = img->comps[0].h;
  
  y  = img->comps[0].data;
  cb = img->comps[1].data;
  cr = img->comps[2].data;
  
  r = (int *)malloc(4LL * maxw * maxh);
  g = (int *)malloc(4LL * maxw * maxh);
  b = (int *)malloc(4LL * maxw * maxh);
  
  d0 = r;
  d1 = g;
  d2 = b;

  if (r && g && b)
  {
    // Process pairs of rows (height is divisible by 2)
    for (i = 0; i < (maxh & 0xFFFFFFFE); i += 2)
    {
      int *ny = &y[maxw];
      int *nr = &r[maxw];
      int *ng = &g[maxw];
      int *nb = &b[maxw];
      
      // Process pairs of columns (width is divisible by 2)
      for (j = 0; j < (maxw & 0xFFFFFFFE); j += 2)
      {
        // Top-left pixel
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
        // Top-right pixel
        sycc_to_rgb(offset, upb, y[1], *cb, *cr, r + 1, g + 1, b + 1);
        
        // Bottom-left pixel
        sycc_to_rgb(offset, upb, *ny, *cb, *cr, nr, ng, nb);
        // Bottom-right pixel
        sycc_to_rgb(offset, upb, ny[1], *cb, *cr, nr + 1, ng + 1, nb + 1);
        
        y  += 2;
        r  += 2;
        g  += 2;
        b  += 2;
        ny += 2;
        nr += 2;
        ng += 2;
        nb += 2;
        
        cb++;
        cr++;
      }
      
      // Handle odd width (remaining 1 column)
      if (j < maxw)
      {
        sycc_to_rgb(offset, upb, *y++, *cb, *cr, r++, g++, b++);
        sycc_to_rgb(offset, upb, *ny, *cb++, *cr++, nr, ng, nb);
      }
      
      // Advance pointers to the next row pair
      y += maxw;
      r += maxw;
      g += maxw;
      b += maxw;
    }
    
    // Handle odd height (remaining 1 row)
    if (i < maxh)
    {
      for (j = 0; j < (maxw & 0xFFFFFFFE); j += 2)
      {
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
        sycc_to_rgb(offset, upb, y[1], *cb, *cr, r + 1, g + 1, b + 1);
        
        y += 2;
        r += 2;
        g += 2;
        b += 2;
        
        cb++;
        cr++;
      }
      
      // Handle odd width in the last row
      if (j < maxw)
      {
        sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
      }
    }
    
    // Free old data and assign the newly allocated RGB buffers
    free(img->comps[0].data);
    img->comps[0].data = d0;
    
    free(img->comps[1].data);
    img->comps[1].data = d1;
    
    free(img->comps[2].data);
    img->comps[2].data = d2;
    
    // Upscale chroma components dimensions to match luma
    img->comps[1].w = maxw;
    img->comps[1].h = maxh;
    img->comps[2].w = maxw;
    img->comps[2].h = maxh;
    
    img->comps[1].dx = img->comps[0].dx;
    img->comps[2].dx = img->comps[0].dx;
    img->comps[1].dy = img->comps[0].dy;
    img->comps[2].dy = img->comps[0].dy;
  }
  else
  {
    // Clean up any successfully allocated buffers if one failed
    if (r) free(r);
    if (g) free(g);
    if (b) free(b);
  }
}