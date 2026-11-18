static void postfillAllChannels(SF_PRIVATE *psf) {
  int ch;
  if (psf->buffer_size - psf->end < psf->blockwidth / 2) {
    for (ch = 0; ch < psf->channels; ch++)
      memmove(psf->float_buffer[ch],
              psf->float_buffer[ch] + psf->buffer_size - psf->blockwidth,
              psf->blockwidth * sizeof(float));
    psf->end_pos -= psf->buffer_size - psf->blockwidth;
    psf->end -= psf->buffer_size - psf->blockwidth;
  }
  for (ch = 0; ch < psf->channels; ch++)
    memset(psf->float_buffer[ch] + psf->end, 0,
           (psf->buffer_size - psf->end) * sizeof(float));
  psf->flags |= 0x0200;
  psf->end += psf->blockwidth / 2;
}