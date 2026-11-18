static void
mcid_char_imp(fz_context *ctx, pdf_document *doc, pdf_cmap *cmap, int wmode, int remove)
{
	if (cmap->obj == NULL)
		return;

	if (remove)
	{
		pdf_dict_del(ctx, cmap->obj, PDF_NAME(UID));
		pdf_dict_del(ctx, cmap->obj, PDF_NAME(CMapName));
	}

	walk_string(ctx, wmode, remove, &cmap->bfr);
	walk_string(ctx, wmode, remove, &cmap->bto);

	if (remove)
		remove = cmap->bfr.start == -1 || cmap->bto.start == -1;
	else
		remove = cmap->bfr.start >= 0 || cmap->bto.start >= 0;

	if (remove)
	{
		if (cmap->bto.start == -1)
			pdf_dict_del(ctx, cmap->obj, PDF_NAME(BTO));
		if (cmap->bfr.start == -1)
			pdf_dict_del(ctx, cmap->obj, PDF_NAME(BFR));

		pdf_drop_obj(ctx, cmap->obj);
		cmap->obj = NULL;

		fz_free(ctx, cmap->bfr.data);
		cmap->bfr.data = NULL;
		fz_free(ctx, cmap->bto.data);
		cmap->bto.data = NULL;
	}
}