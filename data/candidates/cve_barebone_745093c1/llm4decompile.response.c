void mcid_char_imp(fz_context *ctx, pdf_processor *proc, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj)
	{
		if (remove)
		{
			pdf_dict_del(ctx, tr->mcid_obj, (pdf_obj *)((pdf_obj *)1));
			pdf_dict_del(ctx, tr->mcid_obj, (pdf_obj *)((pdf_obj *)2));
		}
		walk_string(ctx, uni, remove, &tr->alt);
		walk_string(ctx, uni, remove, &tr->actualtext);
		if (remove && ((tr->alt.pos == -1) || (tr->actualtext.pos == -1)))
		{
			if (tr->actualtext.pos == -1)
				pdf_dict_del(ctx, tr->mcid_obj, (pdf_obj *)((pdf_obj *)3));
			if (tr->alt.pos == -1)
				pdf_dict_del(ctx, tr->mcid_obj, (pdf_obj *)((pdf_obj *)4));
			pdf_drop_obj(ctx, tr->mcid_obj);
			tr->mcid_obj = NULL;
			fz_free(ctx, tr->alt.utf8);
			tr->alt.utf8 = NULL;
			fz_free(ctx, tr->actualtext.utf8);
			tr->actualtext.utf8 = NULL;
		}
	}
}