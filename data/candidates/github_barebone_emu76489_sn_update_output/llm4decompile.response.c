void update_output(SNG *sng)
{
 int i;


 sng->base_count += sng->base_incr;
 i = sng->base_count >> 24;
 sng->base_count &= 0xffffff;


 sng->noise_count += i;
 if (sng->noise_count & 0x100)
 {
  if (sng->noise_mode)
   sng->noise_seed = (sng->noise_seed >> 1) | (parity(sng->noise_seed & 0x9) << 15);
  else
   sng->noise_seed = (sng->noise_seed >> 1) | ((sng->noise_seed & 0x1) << 15);

  if (sng->noise_fref)
   sng->noise_count -= sng->freq[2];
  else
   sng->noise_count -= sng->noise_freq;
 }
 if (sng->noise_seed & 0x1)
  sng->ch_out[3] += (short)(voltbl[sng->noise_volume] << 4);
 sng->ch_out[3] >>= 1;


 for (i = 0; i < 3; i++)
 {
  sng->count[i] += i;
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
  if (sng->edge[i] && !sng->mute[i])
   sng->ch_out[i] += (short)(voltbl[sng->volume[i]] << 4);
  sng->ch_out[i] >>= 1;
 }
}