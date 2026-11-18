static int vorbis_finish_frame(vorbis_info *vi, int n, int start, int end) {
  int i, ch, old;
  if (vi->blocksize_1) {
    int blocksize = vi->blocksize_1;
    float *window = get_window(vi, blocksize);
    if (window == NULL) return 0;
    for (ch = 0; ch < vi->channels; ++ch) {
      for (i = 0; i < blocksize; ++i) {
        vi->window[ch][i + start] =
            vi->window[ch][i + start] * window[i] +
            vi->pcm[ch][i] * window[blocksize - 1 - i];
      }
    }
  }
  old = vi->blocksize_1;
  vi->blocksize_1 = n - end;
  for (ch = 0; ch < vi->channels; ++ch) {
    for (i = 0; i + end < n; ++i) {
      vi->pcm[ch][i] = vi->window[ch][i + end];
    }
  }
  if (old == 0) return 0;
  if (end > n) end = n;
  vi->total_samples += end - start;
  return end - start;
}