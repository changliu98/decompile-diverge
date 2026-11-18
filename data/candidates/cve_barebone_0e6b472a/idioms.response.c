int AVI_read_audio(struct avi *AVI, void *buf, int bytes, int *continuous)
{
  int ret = 0;
  int left; int todo; int n = bytes;
  if (AVI->mode == 0) {
    AVI_errno = 7;
    return -1;
  }
  if (AVI->track[AVI->aptr].audio_index == ((void *)0)) {
    AVI_errno = 13;
    return -1;
  }
  *continuous = 1;
  while (n > 0) {
    left = AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len - AVI->track[AVI->aptr].audio_posb;
    if (left == 0) {
      if (AVI->track[AVI->aptr].audio_posc < AVI->track[AVI->aptr].audio_chunks - 1) {
        AVI->track[AVI->aptr].audio_posc++;
        AVI->track[AVI->aptr].audio_posb = 0;
        *continuous = 0;
      }
      else
        return ret;
    }
    else {
      if (n < left)
        todo = n;
      else
        todo = AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len - AVI->track[AVI->aptr].audio_posb;
      seek(AVI->fdes, AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].pos + AVI->track[AVI->aptr].audio_posb, 0);
      if (read(AVI->fdes, (char *)buf + ret, todo) != (long)todo) {
        AVI_errno = 3;
        return -1;
      }
      n -= todo;
      ret += todo;
      AVI->track[AVI->aptr].audio_posb += todo;
    }
  }
  return ret;
}