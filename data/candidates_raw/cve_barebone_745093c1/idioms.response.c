void pdf_filter_tag_record(struct fz_context *context, struct pdf_filter_processor *proc, struct tag_record *tr, int uni, int remove)
{
  if (tr->mcid_obj)
  {
    if (remove)
    {
      pdf_filter_tag_set(context, tr->mcid_obj, "alt", "0");
      pdf_filter_tag_set(context, tr->mcid_obj, "actualtext", "0");
    }
    pdf_filter_tag_set_text(context, uni, remove, &tr->alt);
    pdf_filter_tag_set_text(context, uni, remove, &tr->actualtext);
    if (remove)
    {
      int removealt = 1;
      if (tr->alt.pos != -1)
        removealt = (tr->actualtext.pos == -1);
      remove = removealt;
    }
    else
    {
      if (tr->alt.pos < 0 && tr->actualtext.pos < 0)
        remove = 0;
    }
    if (remove)
    {
      if (tr->actualtext.pos == -1)
        pdf_filter_tag_set(context, tr->mcid_obj, "actualtext", "1");
      if (tr->alt.pos == -1)
        pdf_filter_tag_set(context, tr->mcid_obj, "alt", "1");
      pdf_filter_tag_set_end(context, tr->mcid_obj);
      tr->mcid_obj = ((void *)0);
      pdf_filter_tag_free(context, tr->alt.utf8);
      tr->alt.utf8 = ((void *)0);
      pdf_filter_tag_free(context, tr->actualtext.utf8);
      tr->actualtext.utf8 = ((void *)0);
    }
  }
}