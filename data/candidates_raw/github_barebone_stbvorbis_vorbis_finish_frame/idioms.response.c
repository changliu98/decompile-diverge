int vorbis_get_samples(struct vorbis_get *vg, int length, int left, int right)
{
   int i; int j; int k;
   int prevlen;
   float *window;
   if (vg->previous_length)
   {
      prevlen = vg->previous_length;
      window = vorbis_get_window(vg,prevlen);
      if (!window)
         return 0;
      for (i=0; i<vg->channels; i++)
         for (j=0; j<prevlen; j++)
            vg->channel_buffers[i][left + j] =
               vg->channel_buffers[i][left + j] * window[j] +
               vg->previous_window[i][j] * window[prevlen - 1 - j];
   }
   prevlen = vg->previous_length;
   vg->previous_length = length - right;
   for (i=0; i<vg->channels; i++)
      for (j=0; j+right<length; j++)
         vg->previous_window[i][j] = vg->channel_buffers[i][j + right];
   if (prevlen == 0)
      return 0;
   if (right > length)
      right = length;
   vg->samples_output += right - left;
   return right - left;
}