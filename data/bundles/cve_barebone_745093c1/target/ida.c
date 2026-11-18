void __cdecl mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
  bool v5; // [rsp+Fh] [rbp-21h]
  int removea; // [rsp+10h] [rbp-20h]

  removea = remove;
  if ( tr->mcid_obj )
  {
    if ( remove )
    {
      pdf_dict_del(ctx, tr->mcid_obj, (char *)&dword_0 + 1);
      pdf_dict_del(ctx, tr->mcid_obj, (char *)&dword_0 + 2);
    }
    walk_string(ctx, uni, removea, &tr->alt);
    walk_string(ctx, uni, removea, &tr->actualtext);
    if ( removea )
    {
      v5 = 1;
      if ( tr->alt.pos != -1 )
        v5 = tr->actualtext.pos == -1;
      removea = v5;
    }
    else if ( tr->alt.pos >= 0 || tr->actualtext.pos >= 0 )
    {
      removea = 0;
    }
    if ( removea )
    {
      if ( tr->actualtext.pos == -1 )
        pdf_dict_del(ctx, tr->mcid_obj, (char *)&dword_0 + 3);
      if ( tr->alt.pos == -1 )
        pdf_dict_del(ctx, tr->mcid_obj, &byte_4);
      pdf_drop_obj(ctx, tr->mcid_obj);
      tr->mcid_obj = 0LL;
      fz_free(ctx, tr->alt.utf8);
      tr->alt.utf8 = 0LL;
      fz_free(ctx, tr->actualtext.utf8);
      tr->actualtext.utf8 = 0LL;
    }
  }
}