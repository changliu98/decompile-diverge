static _Bool sunxi_mc_is_cluster_empty(unsigned int cluster)
{
    int i;
    for (i = 0; i < SUNXI_CPUS_PER_CLUSTER; i++)
        if (sunxi_mc_smp_cpu_table[cluster][i].cpu != ((void *)0))
            return 0;
    return 1;
}