int vorbis_finish_frame(stb_vorbis *f,int len,int left,int right)

{
  int iVar1;
  float *pfVar2;
  float *w;
  int n;
  int j_1;
  int i_1;
  int j;
  int i;
  int prev;
  int right_local;
  int left_local;
  int len_local;
  stb_vorbis *f_local;
  int local_c;
  
  if (f->previous_length != 0) {
    iVar1 = f->previous_length;
    pfVar2 = get_window(f,iVar1);
    if (pfVar2 == (float *)0x0) {
      return 0;
    }
    for (i_1 = 0; i_1 < f->channels; i_1 = i_1 + 1) {
      for (j_1 = 0; j_1 < iVar1; j_1 = j_1 + 1) {
        f->channel_buffers[i_1][left + j_1] =
             f->channel_buffers[i_1][left + j_1] * pfVar2[j_1] +
             f->previous_window[i_1][j_1] * pfVar2[(iVar1 + -1) - j_1];
      }
    }
  }
  iVar1 = f->previous_length;
  f->previous_length = len - right;
  for (i = 0; i < f->channels; i = i + 1) {
    for (j = 0; right + j < len; j = j + 1) {
      f->previous_window[i][j] = f->channel_buffers[i][right + j];
    }
  }
  if (iVar1 == 0) {
    local_c = 0;
  }
  else {
    right_local = right;
    if (len < right) {
      right_local = len;
    }
    f->samples_output = (right_local - left) + f->samples_output;
    local_c = right_local - left;
  }
  return local_c;
}