void initialise_banding(struct fz_context *context, struct render_details *render, int color)
{
  int bpp; int reps; int runs; int num_bands;
  render->colorspace = output_cs;
  render->format = output_format;
  if (!color) {
    if (render->colorspace == 1) {
      render->colorspace = 0;
      render->format = 0;
    } else if (render->colorspace == 2) {
      render->colorspace = 0;
      if (render->format == 4)
        render->format = 3;
      else
        render->format = 0;
    }
  }
  switch (render->colorspace) {
  case 0:
    bpp = 1;
    break;
  case 1:
    bpp = 2;
    break;
  case 2:
    bpp = 3;
    break;
  }
  reps = (max_band_memory / (min_band_height * (render->ibounds.x1 - render->ibounds.x0) * bpp));
  if (reps < 1)
    reps = 1;
  if (render->num_workers > 0) {
    num_bands = (render->ibounds.y1 - render->ibounds.y0 - min_band_height + 1) / min_band_height;
    runs = (render->num_workers * ((render->num_workers + (reps + num_bands - 1) / reps - 1) / render->num_workers));
    reps = (runs + num_bands - 1) / runs;
  }
  render->band_height_multiple = reps;
  render->bands_rendered = 0;
  if (output_format <= 2) {
    render->bander = band_to_png(context, out);
    render->n = (output_format == 0 ? 1 : 3);
  } else {
    switch (output_format) {
    case 2:
      render->bander = band_to_ps(context, out);
      render->n = 4;
      break;
    case 3:
      render->bander = band_to_ps_raw(context, out);
      render->n = 1;
      break;
    case 4:
      render->bander = band_to_ps_raw(context, out);
      render->n = 4;
      break;
    }
  }
}