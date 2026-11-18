void __cdecl initialise_banding(fz_context *ctx, render_details *render, int color)
{
  int v3; // ecx
  int colorspace; // [rsp+4h] [rbp-3Ch]
  int num_bands; // [rsp+8h] [rbp-38h]
  int runs; // [rsp+Ch] [rbp-34h]
  int reps; // [rsp+10h] [rbp-30h]
  int bpp; // [rsp+1Ch] [rbp-24h]

  render->colorspace = output_cs;
  render->format = output_format;
  if ( !color )
  {
    if ( render->colorspace == 1 )
    {
      render->colorspace = 0;
      render->format = 0;
    }
    else if ( render->colorspace == 2 )
    {
      render->colorspace = 0;
      if ( render->format == 4 )
        render->format = 3;
      else
        render->format = 0;
    }
  }
  colorspace = render->colorspace;
  if ( colorspace )
  {
    if ( colorspace == 1 )
      bpp = 2;
    else
      bpp = 3;
  }
  else
  {
    bpp = 1;
  }
  reps = max_band_memory
       / (unsigned __int64)(min_band_height * (render->ibounds.x1 - render->ibounds.x0) * (__int64)bpp);
  if ( reps < 1 )
    reps = 1;
  if ( render->num_workers > 0 )
  {
    num_bands = (min_band_height + render->ibounds.y1 - render->ibounds.y0 - 1) / min_band_height;
    runs = render->num_workers * ((render->num_workers + (reps + num_bands - 1) / reps - 1) / render->num_workers);
    reps = (runs + num_bands - 1) / runs;
  }
  render->band_height_multiple = reps;
  render->bands_rendered = 0;
  if ( (unsigned int)output_format > 1 )
  {
    switch ( output_format )
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
  else
  {
    render->bander = fz_new_pnm_band_writer(ctx, out);
    v3 = 3;
    if ( !output_format )
      v3 = 1;
    render->n = v3;
  }
}