HSD_finish_res heatshrink_decoder_finish(heatshrink_decoder *decoder)
{
  // Check if the decoder pointer is valid
  if (decoder == NULL) {
    return HSDR_FINISH_ERROR_NULL;
  }
  
  // Check the current state of the decoder
  switch (decoder->state) {
    // If the decoder is in any of the active states (0-5),
    // return whether there is remaining input data.
    // If input_size is non-zero, it indicates more data is needed.
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return (HSD_finish_res)(decoder->input_size != 0);
    // If the decoder is in a terminal or idle state,
    // indicate that more data is not needed.
    default:
      return HSDR_FINISH_MORE;
  }
}