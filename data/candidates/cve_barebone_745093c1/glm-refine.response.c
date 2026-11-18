void __cdecl mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
  if ( !tr->mcid_obj )
    return;

  if ( remove )
  {
    // (char *)&dword_0 + 1 and + 2 correspond to adjacent 1-byte strings in the .rodata section
    pdf_dict_del(ctx, tr->mcid_obj, "E");
    pdf_dict_del(ctx, tr->mcid_obj, "ActualText");
  }

  walk_string(ctx, uni, remove, &tr->alt);
  walk_string(ctx, uni, remove, &tr->actualtext);

  bool should_remove;
  if ( remove )
  {
    // If both positions are -1, they are completely processed/empty
    should_remove = (tr->alt.pos == -1) && (tr->actualtext.pos == -1);
  }
  else if ( tr->alt.pos >= 0 || tr->actualtext.pos >= 0 )
  {
    should_remove = false;
  }
  else
  {
    should_remove = true;
  }

  if ( should_remove )
  {
    if ( tr->actualtext.pos == -1 )
      pdf_dict_del(ctx, tr->mcid_obj, "Lang"); // (char *)&dword_0 + 3
    
    if ( tr->alt.pos == -1 )
      pdf_dict_del(ctx, tr->mcid_obj, "Alt");  // &byte_4

    pdf_drop_obj(ctx, tr->mcid_obj);
    tr->mcid_obj = NULL;
    
    fz_free(ctx, tr->alt.utf8);
    tr->alt.utf8 = NULL;
    
    fz_free(ctx, tr->actualtext.utf8);
    tr->actualtext.utf8 = NULL;
  }
}