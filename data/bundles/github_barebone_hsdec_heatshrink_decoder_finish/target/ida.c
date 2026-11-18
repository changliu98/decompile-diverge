HSD_finish_res __cdecl heatshrink_decoder_finish(heatshrink_decoder *hsd)
{
  int state; // [rsp+0h] [rbp-14h]

  if ( !hsd )
    return -1;
  state = hsd->state;
  if ( !hsd->state )
    return hsd->input_size != 0;
  if ( state == 1 )
    return hsd->input_size != 0;
  if ( (unsigned int)(state - 2) < 4 )
    return hsd->input_size != 0;
  return 1;
}