void __cdecl update_output(SNG *sng)
{
  uint32_t noise_period; 
  uint32_t shifted_seed;
  uint32_t time_step; 
  int i;

  // Advance the global clock divider
  sng->base_count += sng->base_incr;
  time_step = HIBYTE(sng->base_count);
  sng->base_count &= 0xFFFFFFu;

  // Update noise channel (Channel 4)
  sng->noise_count += time_step;
  if ( (sng->noise_count & 0x100) != 0 )
  {
    if ( sng->noise_mode )
    {
      // White noise: shift right and feed back based on parity of bits 0 and 3
      shifted_seed = sng->noise_seed >> 1;
      sng->noise_seed = (parity(sng->noise_seed & 9) << 15) | shifted_seed;
    }
    else
    {
      // Periodic noise: simply shift right and wrap the lowest bit to the top
      sng->noise_seed = ((sng->noise_seed & 1) << 15) | (sng->noise_seed >> 1);
    }
    
    // Determine the frequency period for the noise channel
    noise_period = sng->noise_fref ? sng->freq[2] : sng->noise_freq;
    sng->noise_count -= noise_period;
  }

  // Mix noise channel output
  if ( (sng->noise_seed & 1) != 0 )
    sng->ch_out[3] += 16 * voltbl[2 * sng->noise_volume];
  sng->ch_out[3] >>= 1;

  // Update tone channels (Channels 1 to 3)
  for ( i = 0; i < 3; ++i )
  {
    sng->count[i] += time_step;
    if ( (sng->count[i] & 0x400) != 0 )
    {
      if ( sng->freq[i] <= 1 )
      {
        // If frequency is too low (period <= 1), hold the output high
        sng->edge[i] = 1;
      }
      else
      {
        // Toggle the square wave edge and wrap the counter
        sng->edge[i] = sng->edge[i] == 0;
        sng->count[i] -= sng->freq[i];
      }
    }

    // Mix tone channel output
    if ( sng->edge[i] )
    {
      if ( !sng->mute[i] )
        sng->ch_out[i] += 16 * voltbl[2 * sng->volume[i]];
    }
    sng->ch_out[i] >>= 1;
  }
}