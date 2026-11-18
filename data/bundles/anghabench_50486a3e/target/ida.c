bool __cdecl sunxi_mc_smp_cluster_is_down(unsigned int cluster)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < SUNXI_CPUS_PER_CLUSTER; ++i )
  {
    if ( *(_QWORD *)(*(_QWORD *)(sunxi_mc_smp_cpu_table + 8LL * cluster) + 8LL * i) )
      return 0;
  }
  return 1;
}