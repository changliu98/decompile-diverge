void initialise_banding(fz_context *ctx,render_details *render,int color)

{
  int iVar1;
  int iVar2;
  fz_band_writer *pfVar3;
  int num_bands;
  int runs;
  int reps;
  int w;
  int h;
  int bpp;
  size_t min_band_mem;
  int color_local;
  render_details *render_local;
  fz_context *ctx_local;
  
  render->colorspace = output_cs;
  render->format = output_format;
  if (color == 0) {
    if (render->colorspace == 1) {
      render->colorspace = 0;
      render->format = 0;
    }
    else if (render->colorspace == 2) {
      render->colorspace = 0;
      if (render->format == 4) {
        render->format = 3;
      }
      else {
        render->format = 0;
      }
    }
  }
  if (render->colorspace == 0) {
    bpp = 1;
  }
  else if (render->colorspace == 1) {
    bpp = 2;
  }
  else {
    bpp = 3;
  }
  reps = (int)(max_band_memory /
              (ulong)((long)bpp * (long)((render->ibounds).x1 - (render->ibounds).x0) *
                     (long)min_band_height));
  if (reps < 1) {
    reps = 1;
  }
  if (0 < render->num_workers) {
    iVar1 = (((render->ibounds).y1 - (render->ibounds).y0) + min_band_height + -1) / min_band_height
    ;
    iVar2 = (((iVar1 + reps + -1) / reps + render->num_workers + -1) / render->num_workers) *
            render->num_workers;
    reps = (iVar1 + iVar2 + -1) / iVar2;
  }
  render->band_height_multiple = reps;
  render->bands_rendered = 0;
  if ((output_format == 0) || (output_format == 1)) {
    pfVar3 = fz_new_pnm_band_writer(ctx,out);
    render->bander = pfVar3;
    iVar1 = 3;
    if (output_format == 0) {
      iVar1 = 1;
    }
    render->n = iVar1;
  }
  else if (output_format == 2) {
    pfVar3 = fz_new_pam_band_writer(ctx,out);
    render->bander = pfVar3;
    render->n = 4;
  }
  else if (output_format == 3) {
    pfVar3 = fz_new_pbm_band_writer(ctx,out);
    render->bander = pfVar3;
    render->n = 1;
  }
  else if (output_format == 4) {
    pfVar3 = fz_new_pkm_band_writer(ctx,out);
    render->bander = pfVar3;
    render->n = 4;
  }
  return;
}