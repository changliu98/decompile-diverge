void getCpuid(unsigned int *out, unsigned int ax)
{
    int i;
    unsigned int *info;
    if (ax == 0)
        info = cpuid_basic_info(ax);
    else if (ax == 1)
        info = cpuid_Version_info(ax);
    else if (ax == 2)
        info = cpuid_cache_tlb_info(ax);
    else if (ax == 3)
        info = cpuid_serial_info(ax);
    else if (ax == 4)
        info = cpuid_Deterministic_Cache_Parameters_info(ax);
    else if (ax == 5)
        info = cpuid_MONITOR_MWAIT_Features_info(ax);
    else if (ax == 6)
        info = cpuid_Thermal_Power_Management_info(ax);
    else if (ax == 7)
        info = cpuid_Extended_Feature_Enumeration_info(ax);
    else if (ax == 9)
        info = cpuid_Direct_Cache_Access_info(ax);
    else if (ax == 10)
        info = cpuid_Architectural_Performance_Monitoring_info(ax);
    else if (ax == 11)
        info = cpuid_Extended_Topology_info(ax);
    else if (ax == 13)
        info = cpuid_Processor_Extended_States_info(ax);
    else if (ax == 15)
        info = cpuid_Quality_of_Service_info(ax);
    else if (ax == 0x80000002)
        info = cpuid_brand_part1_info(ax);
    else if (ax == 0x80000003)
        info = cpuid_brand_part2_info(ax);
    else if (ax == 0x80000004)
        info = cpuid_brand_part3_info(ax);
    else
        info = cpuid(ax);

    for (i = 0; i < 4; i++)
        out[i] = info[i];
}