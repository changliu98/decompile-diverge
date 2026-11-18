void sng_update(struct sng *sng)
{
  int i;
  unsigned int count_incr;
  unsigned int noise_freq;
  unsigned int noise_seed;
  count_incr = sng->base_count + sng->base_incr;
  sng->base_count = count_incr & 0xffffff;
  count_incr = count_incr >> 24;
  sng->noise_count += count_incr;
  if (sng->noise_count & 0x100)
  {
    if (sng->noise_mode == 0)
    {
      noise_seed = sng->noise_seed & 0xfffeffff;
      sng->noise_seed = (sng->noise_seed & 1) << 15 | noise_seed;
    }
    else
    {
      noise_seed = sng->noise_seed & 0xfffeffff;
      noise_seed = (noise_seed >> 1) | (get_rand(sng->noise_seed & 0x00000009) << 15);
      sng->noise_seed = noise_seed;
    }
    if (sng->noise_fref)
      noise_freq = sng->freq[2];
    else
      noise_freq = sng->noise_freq;
    sng->noise_count -= noise_freq;
  }
  if (sng->noise_seed & 1)
    sng->ch_out[3] += voltbl[sng->noise_volume][1] * 16;
  sng->ch_out[3] >>= 1;
  for (i = 0; i < 3; i++)
  {
    sng->count[i] += count_incr;
    if (sng->count[i] & 0x400)
    {
      if (sng->freq[i] > 1)
      {
        sng->edge[i] = !sng->edge[i];
        sng->count[i] -= sng->freq[i];
      }
      else
        sng->edge[i] = 1;
    }
    if (sng->edge[i])
    {
      if (!sng->mute[i])
        sng->ch_out[i] += voltbl[sng->volume[i]][1] * 16;
    }
    sng->ch_out[i] >>= 1;
  }
}