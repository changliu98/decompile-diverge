void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
    int leaf = *eax;
    int *info_array;

    if (leaf == 0) {
        info_array = cpuid_basic_info(leaf);
    } else if (leaf == 1) {
        info_array = cpuid_Version_info(leaf);
    } else if (leaf == 2) {
        info_array = cpuid_cache_tlb_info(leaf);
    } else if (leaf == 3) {
        info_array = cpuid_serial_info(leaf);
    } else if (leaf == 4) {
        info_array = cpuid_Deterministic_Cache_Parameters_info(leaf);
    } else if (leaf == 5) {
        info_array = cpuid_MONITOR_MWAIT_Features_info(leaf);
    } else if (leaf == 6) {
        info_array = cpuid_Thermal_Power_Management_info(leaf);
    } else if (leaf == 7) {
        info_array = cpuid_Extended_Feature_Enumeration_info(leaf);
    } else if (leaf == 9) {
        info_array = cpuid_Direct_Cache_Access_info(leaf);
    } else if (leaf == 10) {
        info_array = cpuid_Architectural_Performance_Monitoring_info(leaf);
    } else if (leaf == 11) {
        info_array = cpuid_Extended_Topology_info(leaf);
    } else if (leaf == 13) {
        info_array = cpuid_Processor_Extended_States_info(leaf);
    } else if (leaf == 15) {
        info_array = cpuid_Quality_of_Service_info(leaf);
    } else if (leaf == 0x80000002) {
        info_array = cpuid_brand_part1_info(leaf);
    } else if (leaf == 0x80000003) {
        info_array = cpuid_brand_part2_info(leaf);
    } else if (leaf == 0x80000004) {
        info_array = cpuid_brand_part3_info(leaf);
    } else {
        info_array = cpuid(leaf);
    }

    *eax = info_array[0];
    *ebx = info_array[1];
    *ecx = info_array[3];
    *edx = info_array[2];
}