static int read_header(struct wavpack_context *wpc, WavpackMetadata *wpmd)
{
    int result = 0;
    int bytecount = wpmd->byte_length;
    unsigned char *byteptr = wpmd->data;

    wpc->stream_mode = 0x1;
    wpc->total_samples = 0;
    wpc->crc = 0;
    wpc->channel_mask = 0;
    wpc->channel_id = 0;

    if (wpc->channel_id) {
 free (wpc->channel_id);
 wpc->channel_id = NULL;
    }

    if (bytecount) {
 wpc->channel_mask = *byteptr++;
 wpc->crc |= (*byteptr++ << 8);

 if (--bytecount) {
     wpc->total_samples = *byteptr++ << 16;

     if (--bytecount) {
  int num_channels = *byteptr++;

  wpc->total_samples += *byteptr++;

  if (--bytecount) {
      if (bytecount > num_channels) {

   result = 0;
      }
      else {
   int channel;

   wpc->channel_id = (char *) malloc ((size_t) num_channels);

   if (!wpc->channel_id)
       return 0;

   for (channel = 0; channel < num_channels; channel++) {
       if (bytecount) {
    wpc->channel_id[channel] = *byteptr++;
    bytecount--;
       }
       else
    wpc->channel_id[channel] = (char) channel;
   }
      }
  }
  else
      wpc->total_samples += wpc->num_samples;
     }
     else
  wpc->total_samples += wpc->num_samples;
 }
    }
    else
 result = 1;

    return result;
}