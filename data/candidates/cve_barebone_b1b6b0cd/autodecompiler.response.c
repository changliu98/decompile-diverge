static int
read_new_config_info(struct midistuff *midi, struct sysex_meta *meta)
{
 int nchans;
 int i, len, err;
 unsigned char *data;

 len = meta->len;
 data = meta->data;

 midi->midi_type = 1;
 midi->midi_size = 0;
 midi->midi_chanmask = 0;
 midi->midi_name = '\0';
 if (midi->midi_namebuf != NULL) {
  free(midi->midi_namebuf);
  midi->midi_namebuf = NULL;
 }

 if (len != 0) {
  midi->midi_name = *data++;
  midi->midi_chanmask = (midi->midi_chanmask & ~0xff) | *data++;
  len -= 2;
  if (len != 0) {
   midi->midi_size = *data++ << 16;
   len--;
   if (len != 0) {
    midi->midi_size += *data++;
    len--;
    if (len != 0) {
     if (len > nchans) {
      err = 0;
      goto done;
     }
     midi->midi_namebuf =
      (char *)malloc((size_t)nchans);
     if (midi->midi_namebuf == NULL)
      goto done;
     for (i = 0; ; i++) {
      if (i >= nchans)
       break;
      if (len != 0) {
       midi->midi_namebuf[i] = *data++;
       len--;
      } else
       midi->midi_namebuf[i] = (char)i;
     }
    } else
     midi->midi_size += midi->midi_start;
   } else
    midi->midi_size += midi->midi_end;
  }
 } else
  err = 1;

done:
 return err;
}