void mcid_char_imp(fz_context *ctx,pdf_filter_processor *p,tag_record *tr,int uni,int remove)

{
  bool bVar1;
  int remove_local;
  int uni_local;
  tag_record *tr_local;
  pdf_filter_processor *p_local;
  fz_context *ctx_local;
  
  if (tr->mcid_obj != (pdf_obj *)0x0) {
    if (remove != 0) {
      pdf_dict_del(ctx,tr->mcid_obj,(pdf_obj *)0x1);
      pdf_dict_del(ctx,tr->mcid_obj,(pdf_obj *)0x2);
    }
    walk_string(ctx,uni,remove,&tr->alt);
    walk_string(ctx,uni,remove,&tr->actualtext);
    if (remove == 0) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
      if ((tr->alt).pos != -1) {
        bVar1 = (tr->actualtext).pos == -1;
      }
    }
    if (bVar1) {
      if ((tr->actualtext).pos == -1) {
        pdf_dict_del(ctx,tr->mcid_obj,(pdf_obj *)0x3);
      }
      if ((tr->alt).pos == -1) {
        pdf_dict_del(ctx,tr->mcid_obj,(pdf_obj *)0x4);
      }
      pdf_drop_obj(ctx,tr->mcid_obj);
      tr->mcid_obj = (pdf_obj *)0x0;
      fz_free(ctx,(tr->alt).utf8);
      (tr->alt).utf8 = (char *)0x0;
      fz_free(ctx,(tr->actualtext).utf8);
      (tr->actualtext).utf8 = (char *)0x0;
    }
  }
  return;
}