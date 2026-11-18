void __cdecl initialise_banding(fz_context *ctx, render_details *render, int color)
{
  int colorspace;
  int num_bands;
  int runs;
  int reps;
  int bpp;

  // 1. Initialize colorspace and format from global output settings
  render->colorspace = output_cs;
  render->format = output_format;

  // 2. Force grayscale output if the 'color' flag is disabled
  if (!color)
  {
    if (render->colorspace == 1)
    {
      render->colorspace = 0;
      render->format = 0;
    }
    else if (render->colorspace == 2)
    {
      render->colorspace = 0;
      render->format = (render->format == 4) ? 3 : 0;
    }
  }

  // 3. Determine bytes per pixel (bpp) based on the final colorspace
  colorspace = render->colorspace;
  if (colorspace == 0)
    bpp = 1;
  else if (colorspace == 1)
    bpp = 2;
  else
    bpp = 3;

  // 4. Calculate the number of band repetitions (reps) that fit in memory
  reps = max_band_memory / (unsigned __int64)(min_band_height * (render->ibounds.x1 - render->ibounds.x0) * (__int64)bpp);
  if (reps < 1)
    reps = 1;

  // 5. Adjust reps based on the number of worker threads
  if (render->num_workers > 0)
  {
    num_bands = (min_band_height + render->ibounds.y1 - render->ibounds.y0 - 1) / min_band_height;
    runs = render->num_workers * (((reps + num_bands - 1) / reps + render->num_workers - 1) / render->num_workers);
    reps = (runs + num_bands - 1) / runs;
  }

  render->band_height_multiple = reps;
  render->bands_rendered = 0;

  // 6. Initialize the band writer and component count (n) based on output format
  if (output_format <= 1)
  {
    render->bander = fz_new_pnm_band_writer(ctx, out);
    render->n = output_format ? 3 : 1;
  }
  else
  {
    switch (output_format)
    {
      case 2:
        render->bander = fz_new_pam_band_writer(ctx, out);
        render->n = 4;
        break;
      case 3:
        render->bander = fz_new_pbm_band_writer(ctx, out);
        render->n = 1;
        break;
      case 4:
        render->bander = fz_new_pkm_band_writer(ctx, out);
        render->n = 4;
        break;
    }
  }
}