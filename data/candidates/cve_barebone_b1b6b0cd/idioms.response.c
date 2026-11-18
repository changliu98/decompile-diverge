int read_new_config_info(struct WavpackContext *wpc, struct WavpackMetadata *wpmd)
{
  int i; int nchans; int nbytes = wpmd->byte_length;
  unsigned char *data = wpmd->data;
  wpc->version_five = 1;
  wpc->channel_layout = 0;
  wpc->config.qmode = 0;
  wpc->file_format = 0;
  if (wpc->channel_reordering)
  {
    free_channel_reordering(wpc->channel_reordering);
    wpc->channel_reordering = ((void *)0);
  }
  if (nbytes == 0)
    return 1;
  wpc->file_format = *data++;
  nbytes--;
  if (nbytes == 0)
    return 1;
  wpc->config.qmode = *data | (wpc->config.qmode & 0xff000000);
  data++;
  nbytes--;
  if (nbytes == 0)
    return 1;
  nchans = *data++;
  wpc->channel_layout += nchans;
  nbytes--;
  if (nbytes == 0)
  {
    wpc->channel_layout += wpc->config.num_channels;
    return 1;
  }
  if (nbytes > nchans)
    return 0;
  wpc->channel_reordering = (unsigned char *)
    malloc(nchans);
  if (wpc->channel_reordering == ((void *)0))
    return 1;
  for (i = 0; i < nchans; i++)
  {
    if (nbytes)
    {
      wpc->channel_reordering[i] = *data++;
      nbytes--;
    }
    else
      wpc->channel_reordering[i] = i;
  }
  return 1;
}