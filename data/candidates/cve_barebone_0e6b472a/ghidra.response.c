int AVI_read_audio(avi_t *AVI,u8 *audbuf,int bytes,int *continuous)

{
  u32 uVar1;
  int left;
  s64 ret;
  s64 pos;
  int todo;
  int nr;
  int *continuous_local;
  int bytes_local;
  u8 *audbuf_local;
  avi_t *AVI_local;
  int local_c;
  
  if (AVI->mode == 0) {
    AVI_errno = 7;
    local_c = -1;
  }
  else if (AVI->track[AVI->aptr].audio_index == (audio_index_entry *)0x0) {
    AVI_errno = 0xd;
    local_c = -1;
  }
  else {
    nr = 0;
    if (bytes == 0) {
      AVI->track[AVI->aptr].audio_posc = AVI->track[AVI->aptr].audio_posc + 1;
      AVI->track[AVI->aptr].audio_posb = 0;
    }
    *continuous = 1;
    bytes_local = bytes;
    while (0 < bytes_local) {
      todo = (int)AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len -
             AVI->track[AVI->aptr].audio_posb;
      if (todo == 0) {
        if (AVI->track[AVI->aptr].audio_chunks + -1 <= AVI->track[AVI->aptr].audio_posc) {
          return nr;
        }
        AVI->track[AVI->aptr].audio_posc = AVI->track[AVI->aptr].audio_posc + 1;
        AVI->track[AVI->aptr].audio_posb = 0;
        *continuous = 0;
      }
      else {
        if (bytes_local < todo) {
          todo = bytes_local;
        }
        gf_fseek(AVI->fdes,
                 AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].pos +
                 (long)AVI->track[AVI->aptr].audio_posb,0);
        uVar1 = avi_read(AVI->fdes,(char *)(audbuf + nr),todo);
        if ((ulong)uVar1 != (long)todo) {
          AVI_errno = 3;
          return -1;
        }
        bytes_local = bytes_local - todo;
        nr = todo + nr;
        AVI->track[AVI->aptr].audio_posb = todo + AVI->track[AVI->aptr].audio_posb;
      }
    }
    local_c = nr;
  }
  return local_c;
}