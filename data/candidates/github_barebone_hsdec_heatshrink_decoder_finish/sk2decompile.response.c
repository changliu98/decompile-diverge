int8_t heatshrink_decoder_finish(heatshrink_decoder *hsd) {
  if (hsd == NULL) {
    return -1;
  }
  switch (hsd->state) {
    case 0:
      return hsd->input_size != 0;
    case 1:
      return hsd->input_size != 0;
    case 2:
    case 3:
    case 4:
    case 5:
      return hsd->input_size != 0;
    default:
      return 1;
  }
}