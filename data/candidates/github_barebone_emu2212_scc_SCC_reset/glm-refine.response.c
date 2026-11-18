void __cdecl SCC_reset(SCC *scc)
{
  int i, j;

  if (scc == NULL)
    return;

  // Reset global chip state
  scc->mode = 0;
  scc->active = 0;
  scc->base_adr = 0x9000; // 36864 in hexadecimal

  // Reset all 5 channels
  for (i = 0; i < 5; ++i)
  {
    // Clear the 32-byte waveform table for this channel
    // (Note: The original decompiler output shows j < 5, but typically 
    // SCC waveforms are 32 bytes. If the struct is defined correctly, 
    // sizeof or a macro would be ideal here).
    for (j = 0; j < 5; ++j)
      scc->wave[i][j] = 0;

    scc->count[i] = 0;
    scc->freq[i] = 0;
    scc->phase[i] = 0;
    scc->volume[i] = 0;
    scc->offset[i] = 0;
    scc->rotate[i] = 0;
    scc->ch_out[i] = 0;
  }

  // Clear the register bank
  memset(scc->reg, 0, sizeof(scc->reg));

  // Reset mixer and output flags
  scc->mask = 0;
  scc->ch_enable = 0xFF;      // 255 in hexadecimal (all channels enabled)
  scc->ch_enable_next = 0xFF; // 255 in hexadecimal
  scc->cycle_4bit = 0;
  scc->cycle_8bit = 0;
  scc->refresh = 0;
  scc->out = 0;
}