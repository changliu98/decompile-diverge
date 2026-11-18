static inline void
update_output (SNG * sng)
{

  int i;
  uint32_t incr;

  sng->base_count += sng->base_incr;
  incr = (sng->base_count >> GETA_BITS);
  sng->base_count &= (1 << GETA_BITS) - 1;

  /* Noise */
  sng->noise_count += incr;
  if (sng->noise_count & 0x100)
  {
    if (sng->noise_mode) /* White */
      sng->noise_seed = (sng->noise_seed>>1) | (parity(sng->noise_seed&0x0009)<<15);
    else                 /* Periodic */
      sng->noise_seed = (sng->noise_seed>>1) | ((sng->noise_seed&1)<<15);
    
    if(sng->noise_fref)
      sng->noise_count -= sng->freq[2];
    else
      sng->noise_count -= sng->noise_freq;
  }

  if (sng->noise_seed & 1) 
  {
    sng->ch_out[3] += voltbl[sng->noise_volume] << 4;
  }
  sng->ch_out[3] >>= 1;

  /* Tone */
  for (i = 0; i < 3; i++)
  {
    sng->count[i] += incr;
    if (sng->count[i] & 0x400)
    {
      if (sng->freq[i] > 1)
      {
        sng->edge[i] = !sng->edge[i];
        sng->count[i] -= sng->freq[i];
      }
      else
      {
        sng->edge[i] = 1;
      }
    }

    if (sng->edge[i] && !sng->mute[i])
    {
      sng->ch_out[i] += voltbl[sng->volume[i]] << 4;
    }

    sng->ch_out[i] >>= 1;
  }

}