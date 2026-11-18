void run_cpuid(int eax, int ecx, int *abcd)
{
    int *ptr;
    int i;
    if (eax == 0)
        ptr = cpuid_basic_info(eax);
    else if (eax == 1)
        ptr = cpuid_Version_info(eax);
    else if (eax == 2)
        ptr = cpuid_cache_tlb_info(eax);
    else if (eax == 3)
        ptr = cpuid_serial_info(eax);
    else if (eax == 4)
        ptr = cpuid_Deterministic_Cache_Parameters_info(eax);
    else if (eax == 5)
        ptr = cpuid_MONITOR_MWAIT_Features_info(eax);
    else if (eax == 6)
        ptr = cpuid_Thermal_Power_Management_info(eax);
    else if (eax == 7)
        ptr = cpuid_Extended_Feature_Enumeration_info(eax);
    else if (eax == 9)
        ptr = cpuid_Direct_Cache_Access_info(eax);
    else if (eax == 10)
        ptr = cpuid_Architectural_Performance_Monitoring_info(eax);
    else if (eax == 11)
        ptr = cpuid_Extended_Topology_info(eax);
    else if (eax == 13)
        ptr = cpuid_Processor_Extended_States_info(eax);
    else if (eax == 15)
        ptr = cpuid_Quality_of_Service_info(eax);
    else if (eax == 0x80000002)
        ptr = cpuid_brand_part1_info(eax);
    else if (eax == 0x80000003)
        ptr = cpuid_brand_part2_info(eax);
    else if (eax == 0x80000004)
        ptr = cpuid_brand_part3_info(eax);
    else
        ptr = cpuid(eax);

    for (i = 0; i < 4; i++)
        abcd[i] = ptr[i];
}