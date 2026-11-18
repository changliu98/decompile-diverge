int __cdecl ras_putdatastd(jas_stream_t *out, ras_hdr_t *hdr, jas_image_t *image, int numcmpts, int *cmpts)
{
  jas_seqent_t r_val, g_val, b_val, gray_val;
  int i, x, y, c, v, nz, pad, rowsize;
  unsigned int z;
  jas_matrix_t *data[3];
  __int64 mask;

  // Allocate matrices for each component
  for (i = 0; i < numcmpts; ++i)
  {
    data[i] = jas_matrix_create(
                LODWORD(image->bry_) - LODWORD(image->tly_),
                LODWORD(image->brx_) - LODWORD(image->tlx_));
    if (!data[i])
      __assert_fail(
        "data[i]",
        "/work/harness.c",
        0xF6u,
        "int ras_putdatastd(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *)");
  }

  // Calculate row size and padding
  rowsize = 2 * ((hdr->depth * hdr->width + 15) / 16);
  pad = rowsize - (hdr->depth * hdr->width + 7) / 8;
  hdr->length = rowsize * hdr->height;

  // Process each row
  for (y = 0; y < hdr->height; ++y)
  {
    // Read a row for each component
    for (i = 0; i < numcmpts; ++i)
    {
      if (jas_image_readcmpt(image, cmpts[i], 0LL, y, image->brx_ - image->tlx_, 1LL, data[i]))
        return -1;
    }

    z = 0;
    nz = 0;

    // Process each pixel in the row
    for (x = 0; x < hdr->width; ++x)
    {
      z <<= hdr->depth;

      if (hdr->depth == 24 || hdr->depth == 32)
      {
        // Extract RGB components
        if (data[0]->numrows_ == 1)
          b_val = (*data[0]->rows_)[x];
        else
          b_val = *data[0]->rows_[x];

        if (data[1]->numrows_ == 1)
          g_val = (*data[1]->rows_)[x];
        else
          g_val = *data[1]->rows_[x];

        if (data[2]->numrows_ == 1)
          r_val = (*data[2]->rows_)[x];
        else
          r_val = *data[2]->rows_[x];

        v = ((unsigned __int8)r_val << 16) | ((unsigned __int8)g_val << 8) | (unsigned __int8)b_val;
      }
      else
      {
        // Extract grayscale component
        if (data[0]->numrows_ == 1)
          gray_val = (*data[0]->rows_)[x];
        else
          gray_val = *data[0]->rows_[x];

        v = gray_val;
      }

      // Apply depth mask
      if (hdr->depth == 32)
        mask = -1;
      else
        mask = (1LL << hdr->depth) - 1;

      z |= mask & v;
      nz += hdr->depth;

      // Write complete bytes to stream
      while (nz >= 8)
      {
        c = (unsigned __int8)(z >> (nz - 8));
        if (jas_stream_putc(out, c) == -1)
          return -1;

        nz -= 8;

        if (nz == 32)
          mask = -1;
        else
          mask = (1LL << nz) - 1;

        z &= mask;
      }
    }

    // Write remaining bits in the last byte
    if (nz > 0)
    {
      c = ((1 << nz) - 1) & (z >> (8 - nz));
      if (jas_stream_putc(out, c) == -1)
        return -1;
    }

    // Write padding byte if necessary
    if (pad % 2 && jas_stream_putc(out, 0) == -1)
      return -1;
  }

  // Destroy matrices
  for (i = 0; i < numcmpts; ++i)
    jas_matrix_destroy(data[i]);

  return 0;
}