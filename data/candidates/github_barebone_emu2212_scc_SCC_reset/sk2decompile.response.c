void SCC_reset(SCC *scc) {
  int c, ch;
  if (scc == NULL) return;
  scc->mode = 0;
  scc->test = 0;
  scc->test_reg = 0x9000;
  for (ch = 0; ch < 5; ch++) {
    for (c = 0; c < 5; c++) scc->wave_table[ch][c] = 0;
    scc->wave_pos[ch] = 0;
    scc->wave_phase[ch] = 0;
    scc->wave_freq[ch] = 0;
    scc->wave_vol[ch] = 0;
    scc->wave_env[ch] = 0;
    scc->wave_env_phase[ch] = 0;
    scc->wave_env_freq[ch] = 0;
  }
  memset(scc->wave_out, 0, sizeof(scc->wave_out));
  scc->wave_out_pos = 0;
  scc->noise_freq = 0xff;
  scc->noise_vol = 0xff;
  scc->noise_env = 0;
  scc->noise_env_phase = 0;
  scc->noise_env_freq = 0;
  scc->noise_out = 0;
}