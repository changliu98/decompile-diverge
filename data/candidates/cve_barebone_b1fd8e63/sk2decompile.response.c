void gitn_box_del(gitn_box_t *box) {
  unsigned int i;
  if (box) {
    for (i = 0; i < box->index.count; i++) {
      if (box->index.entry[i].data) {
        gf_free(box->index.entry[i].data);
      }
    }
    if (box->index.entry) {
      gf_free(box->index.entry);
    }
    gf_free(box);
  }
}