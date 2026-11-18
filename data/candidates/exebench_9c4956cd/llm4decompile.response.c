void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx)
{
    int cpu_info[4];

    if (op == 0) {
        cpu_info[0] = cpuid_basic_info(0)[0];
        cpu_info[1] = cpuid_basic_info(0)[1];
        cpu_info[2] = cpuid_basic_info(0)[2];
        cpu_info[3] = cpuid_basic_info(0)[3];
    } else if (op == 1) {
        cpu_info[0] = cpuid_Version_info(1)[0];
        cpu_info[1] = cpuid_Version_info(1)[1];
        cpu_info[2] = cpuid_Version_info(1)[2];
        cpu_info[3] = cpuid_Version_info(1)[3];
    } else if (op == 2) {
        cpu_info[0] = cpuid_cache_tlb_info(2)[0];
        cpu_info[1] = cpuid_cache_tlb_info(2)[1];
        cpu_info[2] = cpuid_cache_tlb_info(2)[2];
        cpu_info[3] = cpuid_cache_tlb_info(2)[3];
    } else if (op == 3) {
        cpu_info[0] = cpuid_serial_info(3)[0];
        cpu_info[1] = cpuid_serial_info(3)[1];
        cpu_info[2] = cpuid_serial_info(3)[2];
        cpu_info[3] = cpuid_serial_info(3)[3];
    } else if (op == 4) {
        cpu_info[0] = cpuid_Deterministic_Cache_Parameters_info(4)[0];
        cpu_info[1] = cpuid_Deterministic_Cache_Parameters_info(4)[1];
        cpu_info[2] = cpuid_Deterministic_Cache_Parameters_info(4)[2];
        cpu_info[3] = cpuid_Deterministic_Cache_Parameters_info(4)[3];
    } else if (op == 5) {
        cpu_info[0] = cpuid_MONITOR_MWAIT_Features_info(5)[0];
        cpu_info[1] = cpuid_MONITOR_MWAIT_Features_info(5)[1];
        cpu_info[2] = cpuid_MONITOR_MWAIT_Features_info(5)[2];
        cpu_info[3] = cpuid_MONITOR_MWAIT_Features_info(5)[3];
    } else if (op == 6) {
        cpu_info[0] = cpuid_Thermal_Power_Management_info(6)[0];
        cpu_info[1] = cpuid_Thermal_Power_Management_info(6)[1];
        cpu_info[2] = cpuid_Thermal_Power_Management_info(6)[2];
        cpu_info[3] = cpuid_Thermal_Power_Management_info(6)[3];
    } else if (op == 7) {
        cpu_info[0] = cpuid_Extended_Feature_Enumeration_info(7)[0];
        cpu_info[1] = cpuid_Extended_Feature_Enumeration_info(7)[1];
        cpu_info[2] = cpuid_Extended_Feature_Enumeration_info(7)[2];
        cpu_info[3] = cpuid_Extended_Feature_Enumeration_info(7)[3];
    } else if (op == 9) {
        cpu_info[0] = cpuid_Direct_Cache_Access_info(9)[0];
        cpu_info[1] = cpuid_Direct_Cache_Access_info(9)[1];
        cpu_info[2] = cpuid_Direct_Cache_Access_info(9)[2];
        cpu_info[3] = cpuid_Direct_Cache_Access_info(9)[3];
    } else if (op == 10) {
        cpu_info[0] = cpuid_Architectural_Performance_Monitoring_info(10)[0];
        cpu_info[1] = cpuid_Architectural_Performance_Monitoring_info(10)[1];
        cpu_info[2] = cpuid_Architectural_Performance_Monitoring_info(10)[2];
        cpu_info[3] = cpuid_Architectural_Performance_Monitoring_info(10)[3];
    } else if (op == 11) {
        cpu_info[0] = cpuid_Extended_Topology_info(11)[0];
        cpu_info[1] = cpuid_Extended_Topology_info(11)[1];
        cpu_info[2] = cpuid_Extended_Topology_info(11)[2];
        cpu_info[3] = cpuid_Extended_Topology_info(11)[3];
    } else if (op == 13) {
        cpu_info[0] = cpuid_Processor_Extended_States_info(13)[0];
        cpu_info[1] = cpuid_Processor_Extended_States_info(13)[1];
        cpu_info[2] = cpuid_Processor_Extended_States_info(13)[2];
        cpu_info[3] = cpuid_Processor_Extended_States_info(13)[3];
    } else if (op == 15) {
        cpu_info[0] = cpuid_Quality_of_Service_info(15)[0];
        cpu_info[1] = cpuid_Quality_of_Service_info(15)[1];
        cpu_info[2] = cpuid_Quality_of_Service_info(15)[2];
        cpu_info[3] = cpuid_Quality_of_Service_info(15)[3];
    } else if (op == 0x80000002) {
        cpu_info[0] = cpuid_brand_part1_info(0x80000002)[0];
        cpu_info[1] = cpuid_brand_part1_info(0x80000002)[1];
        cpu_info[2] = cpuid_brand_part1_info(0x80000002)[2];
        cpu_info[3] = cpuid_brand_part1_info(0x80000002)[3];
    } else if (op == 0x80000003) {
        cpu_info[0] = cpuid_brand_part2_info(0x80000003)[0];
        cpu_info[1] = cpuid_brand_part2_info(0x80000003)[1];
        cpu_info[2] = cpuid_brand_part2_info(0x80000003)[2];
        cpu_info[3] = cpuid_brand_part2_info(0x80000003)[3];
    } else if (op == 0x80000004) {
        cpu_info[0] = cpuid_brand_part3_info(0x80000004)[0];
        cpu_info[1] = cpuid_brand_part3_info(0x80000004)[1];
        cpu_info[2] = cpuid_brand_part3_info(0x80000004)[2];
        cpu_info[3] = cpuid_brand_part3_info(0x80000004)[3];
    } else {
        cpu_info[0] = cpuid(op)[0];
        cpu_info[1] = cpuid(op)[1];
        cpu_info[2] = cpuid(op)[2];
        cpu_info[3] = cpuid(op)[3];
    }

    *eax = cpu_info[0];
    *ebx = cpu_info[1];
    *ecx = cpu_info[2];
    *edx = cpu_info[3];
}