nsgif_error __cdecl nsgif_frame_decode(nsgif_t *gif, uint32_t frame, nsgif_bitmap_t **bitmap)
{
  uint32_t f; // [rsp+4h] [rbp-2Ch]
  nsgif_error ret; // [rsp+8h] [rbp-28h]
  uint32_t start_frame; // [rsp+Ch] [rbp-24h]

  if ( frame >= gif->info.frame_count )
    return 3;
  if ( gif->decoded_frame == frame )
  {
    *bitmap = gif->frame_image;
    return 0;
  }
  else
  {
    if ( gif->decoded_frame >= frame || gif->decoded_frame == -1 )
      start_frame = 0;
    else
      start_frame = nsgif__frame_next(gif, 0, gif->decoded_frame);
    for ( f = start_frame; f <= frame; ++f )
    {
      ret = nsgif__process_frame(gif, f, 1);
      if ( ret )
        return ret;
    }
    *bitmap = gif->frame_image;
    return 0;
  }
}