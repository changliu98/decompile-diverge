bool sunxi_mc_smp_cluster_is_down(unsigned int cluster)
{
	int cpu;

	for (cpu = 0; cpu < SUNXI_CPUS_PER_CLUSTER; cpu++)
		if (sunxi_mc_smp_cpu_table[cluster][cpu])
			return false;

	return true;
}