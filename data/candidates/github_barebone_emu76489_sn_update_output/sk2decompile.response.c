static void update_output(YM2612 *ym2612) {
  int i;
  int step;
  ym2612->cycles += ym2612->step;
  step = (ym2612->cycles >> 24) & 0xff;
  ym2612->cycles &= 0xffffff;
  ym2612->noise_cnt += step;
  if (ym2612->noise_cnt & 0x100) {
    if (ym2612->noise_type) {
      ym2612->noise >>= 1;
      ym2612->noise |= (parity(ym2612->noise & 9) << 15);
    } else {
      ym2612->noise >>= 1;
      ym2612->noise |= (ym2612->noise & 1) << 15;
    }
    if (ym2612->noise_freq)
      ym2612->noise_cnt -= ym2612->noise_freq_tbl[2];
    else
      ym2612->noise_cnt -= ym2612->noise_freq_tbl_1;
  }
  if (ym2612->noise & 1)
    ym2612->output[3] += volume_table[ym2612->noise_volume << 1] << 4;
  ym2612->output[3] >>= 1;
  for (i = 0; i < 3; i++) {
    ym2612->cnt[i] += step;
    if (ym2612->cnt[i] & 0x400) {
      if (ym2612->noise_freq_tbl[i] > 1) {
        ym2612->env_cnt[i] = !ym2612->env_cnt[i];
        ym2612->cnt[i] -= ym2612->noise_freq_tbl[i];
      } else
        ym2612->env_cnt[i] = 1;
    }
    if (ym2612->env_cnt[i] && !ym2612->env_cnt_halt[i])
      ym2612->output[i] += volume_table[ym2612->volume[i] << 1] << 4;
    ym2612->output[i] >>= 1;
  }
}