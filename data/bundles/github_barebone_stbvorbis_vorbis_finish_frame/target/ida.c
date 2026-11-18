int __cdecl vorbis_finish_frame(stb_vorbis *f, int len, int left, int right)
{
  float *w; // [rsp+0h] [rbp-40h]
  int n; // [rsp+Ch] [rbp-34h]
  int j_0; // [rsp+10h] [rbp-30h]
  int i_0; // [rsp+14h] [rbp-2Ch]
  int j; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  int prev; // [rsp+20h] [rbp-20h]

  if ( f->previous_length )
  {
    n = f->previous_length;
    w = get_window(f, n);
    if ( !w )
      return 0;
    for ( i_0 = 0; i_0 < f->channels; ++i_0 )
    {
      for ( j_0 = 0; j_0 < n; ++j_0 )
        f->channel_buffers[i_0][j_0 + left] = (float)(f->channel_buffers[i_0][j_0 + left] * w[j_0])
                                            + (float)(f->previous_window[i_0][j_0] * w[n - 1 - j_0]);
    }
  }
  prev = f->previous_length;
  f->previous_length = len - right;
  for ( i = 0; i < f->channels; ++i )
  {
    for ( j = 0; j + right < len; ++j )
      f->previous_window[i][j] = f->channel_buffers[i][j + right];
  }
  if ( !prev )
    return 0;
  if ( len < right )
    right = len;
  f->samples_output += right - left;
  return right - left;
}