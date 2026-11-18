__attribute__((used)) static int sunxi_mc_smp_cluster_is_down(unsigned int cpu)
{
	int i = 0;
	bool ret;

	while (true) {
		if (i >= SUNXI_CPUS_PER_CLUSTER)
			break;

		if (sunxi_mc_smp_cpu_table[cpu][i] == 0) {
			i++;
			continue;
		}

		ret = readl(sunxi_mc_smp_cpu_table[cpu][i]);
		if (ret & SUNXI_MC_SMP_CPU_OFF)
			writel(readl(sunxi_mc_smp_cpu_table[cpu][i]) &
			       ~SUNXI_MC_SMP_CPU_OFF,
			       sunxi_mc_smp_cpu_table[cpu][i]);

		return false;
	}

	return true;
}