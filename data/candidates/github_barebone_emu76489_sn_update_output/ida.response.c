void __cdecl update_output(SNG *sng)
{
  uint32_t noise_freq; // edx
  uint32_t v2; // [rsp+Ch] [rbp-14h]
  uint32_t incr; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]

  sng->base_count += sng->base_incr;
  incr = HIBYTE(sng->base_count);
  sng->base_count &= 0xFFFFFFu;
  sng->noise_count += incr;
  if ( (sng->noise_count & 0x100) != 0 )
  {
    if ( sng->noise_mode )
    {
      v2 = sng->noise_seed >> 1;
      sng->noise_seed = (parity(sng->noise_seed & 9) << 15) | v2;
    }
    else
    {
      sng->noise_seed = ((sng->noise_seed & 1) << 15) | (sng->noise_seed >> 1);
    }
    if ( sng->noise_fref )
      noise_freq = sng->freq[2];
    else
      noise_freq = sng->noise_freq;
    sng->noise_count -= noise_freq;
  }
  if ( (sng->noise_seed & 1) != 0 )
    sng->ch_out[3] += 16 * voltbl[2 * sng->noise_volume];
  sng->ch_out[3] >>= 1;
  for ( i = 0; i < 3; ++i )
  {
    sng->count[i] += incr;
    if ( (sng->count[i] & 0x400) != 0 )
    {
      if ( sng->freq[i] <= 1 )
      {
        sng->edge[i] = 1;
      }
      else
      {
        sng->edge[i] = sng->edge[i] == 0;
        sng->count[i] -= sng->freq[i];
      }
    }
    if ( sng->edge[i] )
    {
      if ( !sng->mute[i] )
        sng->ch_out[i] += 16 * voltbl[2 * sng->volume[i]];
    }
    sng->ch_out[i] >>= 1;
  }
}