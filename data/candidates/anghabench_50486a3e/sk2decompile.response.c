static bool sunxi_mc_smp_cluster_is_down(unsigned int cluster) {
  int i;
  for (i = 0; i < SUNXI_MC_SMP_MAX_CHANNELS; i++)
    if (sunxi_mc_smp_channel_map[cluster][i]) return false;
  return true;
}