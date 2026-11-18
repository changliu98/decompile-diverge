bool __cdecl sunxi_mc_smp_cluster_is_down(unsigned int cluster)
{
  unsigned long **cluster_ptr;
  int i;

  cluster_ptr = (unsigned long **)sunxi_mc_smp_cpu_table[cluster];

  for (i = 0; i < SUNXI_CPUS_PER_CLUSTER; ++i)
  {
    if (cluster_ptr[i])
      return false;
  }
  return true;
}