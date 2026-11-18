void initialise_banding(fz_context *ctx, render_details *render, int color)
{
	int num_bands;
	int runs;
	int reps;
	int w, h;
	int bpp;
	size_t min_band_mem;

	render->colorspace = output_cs;
	render->format = output_format;

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
			if (render->format == 4)
				render->format = 3;
			else
				render->format = 0;
		}
	}

	if (render->colorspace == 0)
		bpp = 1;
	else if (render->colorspace == 1)
		bpp = 2;
	else
		bpp = 3;

	w = render->ibounds.x1 - render->ibounds.x0;
	min_band_mem = w * bpp * min_band_height;
	reps = max_band_memory / min_band_mem;
	if (reps < 1)
		reps = 1;

	if (render->num_workers > 0)
	{
		num_bands = (render->ibounds.y1 - render->ibounds.y0 + min_band_height - 1) / min_band_height;
		runs = (num_bands + reps - 1) / reps;
		runs = (runs + render->num_workers - 1) / render->num_workers;
		runs = (runs * render->num_workers);
		reps = (num_bands + runs - 1) / runs;
	}

	render->band_height_multiple = reps;
	render->bands_rendered = 0;

	if (output_format == 0 || output_format == 1)
	{
		render->bander = fz_new_pnm_band_writer(ctx, out);
		render->n = output_format == 0 ? 1 : 3;
	}
	else if (output_format == 2)
	{
		render->bander = fz_new_pam_band_writer(ctx, out);
		render->n = 4;
	}
	else if (output_format == 3)
	{
		render->bander = fz_new_pbm_band_writer(ctx, out);
		render->n = 1;
	}
	else if (output_format == 4)
	{
		render->bander = fz_new_pkm_band_writer(ctx, out);
		render->n = 4;
	}
}