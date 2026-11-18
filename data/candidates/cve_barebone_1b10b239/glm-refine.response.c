int __cdecl read_new_config_info(WavpackContext *wpc, WavpackMetadata *wpmd)
{
  unsigned __int8 *byteptr;
  int bytecnt;
  int nchans;
  int i;

  bytecnt = wpmd->byte_length;
  byteptr = (unsigned __int8 *)wpmd->data;
  
  wpc->version_five = 1;
  wpc->channel_layout = 0;
  wpc->config.qmode = 0;
  wpc->file_format = 0;
  
  if (wpc->channel_reordering)
  {
    free(wpc->channel_reordering);
    wpc->channel_reordering = 0LL;
  }
  
  if (!bytecnt)
    return 1;
    
  // Byte 0: File format
  wpc->file_format = *byteptr;
  
  // Byte 1: qmode (preserves original upper 24 bits)
  wpc->config.qmode = byteptr[1] | (wpc->config.qmode & 0xFFFFFF00);
  bytecnt -= 2;
  if (!bytecnt)
    return 1;
    
  // Byte 2: High byte of channel_layout
  wpc->channel_layout = byteptr[2] << 16;
  bytecnt--;
  if (!bytecnt)
  {
    wpc->channel_layout += wpc->config.num_channels;
    return 1;
  }
  
  // Byte 3: Number of channels (low byte of channel_layout)
  nchans = byteptr[3];
  wpc->channel_layout += nchans;
  bytecnt--;
  if (!bytecnt)
    return 1;
    
  // Remaining bytes: Channel reordering mapping
  if (bytecnt <= nchans)
  {
    wpc->channel_reordering = (unsigned __int8 *)malloc(nchans);
    if (wpc->channel_reordering)
    {
      byteptr += 4;
      for (i = 0; i < nchans; ++i)
      {
        if (bytecnt)
        {
          wpc->channel_reordering[i] = *byteptr++;
          --bytecnt;
        }
        else
        {
          wpc->channel_reordering[i] = i;
        }
      }
    }
    return 1;
  }
  
  return 0;
}