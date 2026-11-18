void update_output(SNG *sng)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint32_t incr;
  int i;
  SNG *sng_local;
  
  sng->base_count = sng->base_incr + sng->base_count;
  uVar2 = sng->base_count >> 0x18;
  sng->base_count = sng->base_count & 0xffffff;
  sng->noise_count = uVar2 + sng->noise_count;
  if ((sng->noise_count & 0x100) != 0) {
    if (sng->noise_mode == 0) {
      sng->noise_seed = sng->noise_seed >> 1 | (sng->noise_seed & 1) << 0xf;
    }
    else {
      uVar1 = sng->noise_seed;
      iVar3 = parity(sng->noise_seed & 9);
      sng->noise_seed = uVar1 >> 1 | iVar3 << 0xf;
    }
    if (sng->noise_fref == 0) {
      sng->noise_count = sng->noise_count - sng->noise_freq;
    }
    else {
      sng->noise_count = sng->noise_count - sng->freq[2];
    }
  }
  if ((sng->noise_seed & 1) != 0) {
    sng->ch_out[3] = sng->ch_out[3] + (short)(voltbl[sng->noise_volume] << 4);
  }
  sng->ch_out[3] = sng->ch_out[3] >> 1;
  for (i = 0; i < 3; i = i + 1) {
    sng->count[i] = uVar2 + sng->count[i];
    if ((sng->count[i] & 0x400) != 0) {
      if (sng->freq[i] < 2) {
        sng->edge[i] = 1;
      }
      else {
        sng->edge[i] = (uint)((sng->edge[i] != 0 ^ 0xffU) & 1);
        sng->count[i] = sng->count[i] - sng->freq[i];
      }
    }
    if ((sng->edge[i] != 0) && (sng->mute[i] == 0)) {
      sng->ch_out[i] = sng->ch_out[i] + (short)(voltbl[sng->volume[i]] << 4);
    }
    sng->ch_out[i] = sng->ch_out[i] >> 1;
  }
  return;
}