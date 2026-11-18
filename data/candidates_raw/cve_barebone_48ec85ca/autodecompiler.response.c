__attribute__((used)) static void
band_write_header(fz_context *ctx, band_writer *writer, int color)
{
	writer->cs = output_cs;
	writer->format = output_format;

	if (!color)
	{
		if (writer->cs == 1)
		{
			writer->cs = 0;
			writer->format = 0;
		}
		else if (writer->cs == 2)
		{
			writer->cs = 0;
			if (writer->format == 4)
				writer->format = 3;
			else
				writer->format = 0;
		}
	}

	if (writer->cs)
	{
		int n = writer->cs;
		int w, h, bpp, mem, runs, bands, reps;

		if (n == 0) bpp = 1;
		else if (n == 1) bpp = 2;
		else if (n == 2) bpp = 3;
		else bpp = 4;

		w = writer->xres - writer->begin.x;
		mem = w * bpp * min_band_height;
		reps = max_band_memory / mem;
		if (reps < 1)
			reps = 1;

		if (writer->yres > 0)
		{
			h = writer->yres - writer->begin.y;
			bands = (h + min_band_height - 1) / min_band_height;
			runs = (bands + reps - 1) / reps;
			runs = ((runs + writer->yres - 1) / writer->yres) * writer->yres;
			reps = (bands + runs - 1) / runs;
		}

		writer->reps = reps;
		writer->count = 0;

		if (output_format == 0 || output_format == 1)
		{
			writer->band_writer = fz_new_pnm_band_writer(ctx, out);
			writer->channels = output_format == 0 ? 1 : 3;
		}
		else if (output_format == 2)
		{
			writer->band_writer = fz_new_pam_band_writer(ctx, out);
			writer->channels = 4;
		}
		else if (output_format == 3)
		{
			writer->band_writer = fz_new_pbm_band_writer(ctx, out);
			writer->channels = 1;
		}
		else if (output_format == 4)
		{
			writer->band_writer = fz_new_pkm_band_writer(ctx, out);
			writer->channels = 4;
		}
	}
}