HSD_finish_res __cdecl heatshrink_decoder_finish(heatshrink_decoder *hsd)
{
  if (!hsd)
    return -1;

  // If the state is 6 or higher, the decoder is actively processing or flushing
  if (hsd->state >= 6)
    return 1;

  // For all other states (0 through 5), the decoder is done only if 
  // there is no more input left to process.
  return hsd->input_size != 0;
}