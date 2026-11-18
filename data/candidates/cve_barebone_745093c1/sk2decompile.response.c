static void mcid_char_imp(fz_context *ctx, pdf_document *doc,
                          pdf_font_desc *font, int cid, int eoc) {
  if (!font->cid_to_gid) return;
  if (eoc) {
    pdf_dict_del(ctx, font->cid_to_gid, "A");
    pdf_dict_del(ctx, font->cid_to_gid, "D");
  }
  walk_string(ctx, cid, eoc, &font->cid_to_ucs);
  walk_string(ctx, cid, eoc, &font->cid_to_name);
  if (eoc)
    eoc = font->cid_to_ucs.len == -1 || font->cid_to_name.len == -1;
  else
    eoc = font->cid_to_ucs.len >= 0 || font->cid_to_name.len >= 0;
  if (eoc) {
    if (font->cid_to_name.len == -1) pdf_dict_del(ctx, font->cid_to_gid, "T");
    if (font->cid_to_ucs.len == -1) pdf_dict_del(ctx, font->cid_to_gid, "C");
    pdf_drop_obj(ctx, font->cid_to_gid);
    font->cid_to_gid = NULL;
    fz_free(ctx, font->cid_to_ucs.data);
    font->cid_to_ucs.data = NULL;
    fz_free(ctx, font->cid_to_name.data);
    font->cid_to_name.data = NULL;
  }
}