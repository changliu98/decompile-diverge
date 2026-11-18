bool sunxi_mc_smp_cluster_is_down(uint cluster)

{
  int i;
  uint cluster_local;
  
  i = 0;
  while( true ) {
    if (SUNXI_CPUS_PER_CLUSTER <= i) {
      return 1;
    }
    if (sunxi_mc_smp_cpu_table[cluster][i] != 0) break;
    i = i + 1;
  }
  return 0;
}