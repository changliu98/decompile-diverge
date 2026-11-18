int ImagingPcxDecode(struct Imaging *im, struct ImagingCodecState *state, unsigned char *buf, long bytes)
{
  unsigned char *p = (const unsigned char *)buf;
  if (!is_mode(im->mode, "1") && state->xsize > (state->bytes * 8))
  {
    state->errcode = -1;
    return -1;
  }
  for (; bytes >= 1;)
  {
    if (p[0] & 0xc0)
    {
      if (bytes < 2)
        return p - (unsigned char *)buf;
      unsigned char n = p[0] & 0x3f;
      for (; n > 0 && state->x < state->bytes;)
      {
        state->buffer[state->x++] = p[1];
        n--;
      }
      p += 2;
      bytes -= 2;
    }
    else
    {
      state->buffer[state->x++] = p[0];
      p += 1;
      bytes -= 1;
    }
    if (state->x >= state->bytes)
    {
      if (state->bytes % state->xsize && state->bytes > state->xsize)
      {
        int bands = state->bytes / state->xsize;
        int stride = state->bytes / bands;
        int i;
        for (i = 1; i < bands; i++)
          png_to_1_row(&state->buffer[state->xsize * i],
                       &state->buffer[stride * i],
                       state->xsize);
      }
      state->shuffle(&im->image[state->y][im->pixelsize * state->xoff],
                    state->buffer,
                    state->xsize);
      state->x = 0;
      if (++state->y >= state->ysize)
        return -1;
    }
  }
  return p - (unsigned char *)buf;
}