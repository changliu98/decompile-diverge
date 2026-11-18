int heatshrink_finish(struct heatshrink_decoder *hsd)
{
  if (hsd == ((void *)0))
    return -1;
  switch (hsd->state) {
  case HEATSHRINK_STATE_DONE:
  case HEATSHRINK_STATE_INPUT:
    if (hsd->input_size == 0)
      return 0;
    break;
  case HEATSHRINK_STATE_OUTPUT:
  case HEATSHRINK_STATE_OUTPUT_CONT:
  case HEATSHRINK_STATE_OUTPUT_CONT2:
  case HEATSHRINK_STATE_OUTPUT_CONT3:
    return 1;
  default:
    return 1;
  }
  return 0;
}