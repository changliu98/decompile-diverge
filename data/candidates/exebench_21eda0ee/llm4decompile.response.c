void do_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
    int leaf = *eax;
    unsigned int *info;
    if (leaf == 0)
        info = cpuid_basic_info(leaf);
    else if (leaf == 1)
        info = cpuid_Version_info(leaf);
    else if (leaf == 2)
        info = cpuid_cache_tlb_info(leaf);
    else if (leaf == 3)
        info = cpuid_serial_info(leaf);
    else if (leaf == 4)
        info = cpuid_Deterministic_Cache_Parameters_info(leaf);
    else if (leaf == 5)
        info = cpuid_MONITOR_MWAIT_Features_info(leaf);
    else if (leaf == 6)
        info = cpuid_Thermal_Power_Management_info(leaf);
    else if (leaf == 7)
        info = cpuid_Extended_Feature_Enumeration_info(leaf);
    else if (leaf == 9)
        info = cpuid_Direct_Cache_Access_info(leaf);
    else if (leaf == 10)
        info = cpuid_Architectural_Performance_Monitoring_info(leaf);
    else if (leaf == 11)
        info = cpuid_Extended_Topology_info(leaf);
    else if (leaf == 13)
        info = cpuid_Processor_Extended_States_info(leaf);
    else if (leaf == 15)
        info = cpuid_Quality_of_Service_info(leaf);
    else if (leaf == 0x80000002)
        info = cpuid_brand_part1_info(leaf);
    else if (leaf == 0x80000003)
        info = cpuid_brand_part2_info(leaf);
    else if (leaf == 0x80000004)
        info = cpuid_brand_part3_info(leaf);
    else
        info = cpuid(leaf);

    *eax = info[0];
    *ebx = info[1];
    *ecx = info[2];
    *edx = info[3];
}