void SCC_reset(SCC *scc_instance)
{
  // Reset the SCC hardware state if the pointer is valid
  if (scc_instance) {
    // Reset control mode and active status flags
    scc_instance->mode = 0;
    scc_instance->active = 0;
    // Reset the base memory address to default value
    scc_instance->base_adr = 0x9000;

    // Iterate through each of the 5 sound channels
    for (int channel_index = 0; channel_index < 5; channel_index++) {
      // Clear the waveform lookup table for the current channel
      for (int wave_index = 0; wave_index < 5; wave_index++) {
        scc_instance->wave[channel_index][wave_index] = '\0';
      }
      // Reset channel-specific parameters to zero
      scc_instance->count[channel_index] = 0;
      scc_instance->freq[channel_index] = 0;
      scc_instance->phase[channel_index] = 0;
      scc_instance->volume[channel_index] = 0;
      scc_instance->offset[channel_index] = 0;
      scc_instance->rotate[channel_index] = 0;
      scc_instance->ch_out[channel_index] = 0;
    }

    // Clear the entire register map (64 bytes)
    memset(scc_instance->reg, 0, 0x40);

    // Reset interrupt mask and channel enable states
    scc_instance->mask = 0;
    scc_instance->ch_enable = 0xff;
    scc_instance->ch_enable_next = 0xff;

    // Reset timing counters and output buffers
    scc_instance->cycle_4bit = 0;
    scc_instance->cycle_8bit = 0;
    scc_instance->refresh = 0;
    scc_instance->out = 0;
  }
}