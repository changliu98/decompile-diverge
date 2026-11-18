heatshrink_decoder *heatshrink_decoder_alloc(unsigned short window_sz2,
                                             unsigned char lookahead,
                                             unsigned char index_size) {
  if (lookahead < 4 || lookahead > 15 || window_sz2 == 0 || index_size < 3 ||
      index_size >= lookahead) {
    return NULL;
  }
  size_t size = sizeof(heatshrink_decoder) + (1 << lookahead) + window_sz2;
  heatshrink_decoder *hsd = (heatshrink_decoder *)malloc(size);
  if (hsd == NULL) {
    return NULL;
  }
  hsd->window_sz2 = window_sz2;
  hsd->lookahead = lookahead;
  hsd->index_size = index_size;
  heatshrink_decoder_reset(hsd);
  return hsd;
}