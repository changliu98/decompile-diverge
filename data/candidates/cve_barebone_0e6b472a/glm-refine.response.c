int __cdecl AVI_read_audio(avi_t *AVI, u8 *audbuf, int bytes, int *continuous)
{
  track_t *track;
  int nr;
  int bytesa;

  // Check if file is opened in read mode
  if (!AVI->mode) {
    AVI_errno = 7;
    return -1;
  }

  track = &AVI->track[AVI->aptr];

  // Check if audio index exists
  if (!track->audio_index) {
    AVI_errno = 13;
    return -1;
  }

  // If 0 bytes are requested, advance the chunk pointer and reset byte offset
  if (bytes == 0) {
    track->audio_posc++;
    track->audio_posb = 0;
  }

  *continuous = 1;
  nr = 0;
  bytesa = bytes;

  while (bytesa > 0) {
    int left = (int)track->audio_index[track->audio_posc].len - track->audio_posb;

    if (left > 0) {
      int todo = (bytesa >= left) ? left : bytesa;

      gf_fseek(AVI->fdes, track->audio_posb + track->audio_index[track->audio_posc].pos, 0);
      
      if (avi_read(AVI->fdes, (char *)&audbuf[nr], todo) != (__int64)todo) {
        AVI_errno = 3;
        return -1;
      }

      bytesa -= todo;
      nr += todo;
      track->audio_posb += todo;
    } else {
      // No bytes left in the current chunk, move to the next chunk
      if (track->audio_posc >= track->audio_chunks - 1)
        return nr;

      track->audio_posc++;
      track->audio_posb = 0;
      *continuous = 0;
    }
  }

  return nr;
}