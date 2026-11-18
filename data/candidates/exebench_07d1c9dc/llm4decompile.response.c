void cpuid_count(uint32_t leaf, uint32_t count, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
 int cpu_info[4];
 int *p = cpu_info;

 if (leaf == 0)
  p = cpuid_basic_info(leaf);
 else if (leaf == 1)
  p = cpuid_Version_info(leaf);
 else if (leaf == 2)
  p = cpuid_cache_tlb_info(leaf);
 else if (leaf == 3)
  p = cpuid_serial_info(leaf);
 else if (leaf == 4)
  p = cpuid_Deterministic_Cache_Parameters_info(leaf);
 else if (leaf == 5)
  p = cpuid_MONITOR_MWAIT_Features_info(leaf);
 else if (leaf == 6)
  p = cpuid_Thermal_Power_Management_info(leaf);
 else if (leaf == 7)
  p = cpuid_Extended_Feature_Enumeration_info(leaf);
 else if (leaf == 9)
  p = cpuid_Direct_Cache_Access_info(leaf);
 else if (leaf == 10)
  p = cpuid_Architectural_Performance_Monitoring_info(leaf);
 else if (leaf == 11)
  p = cpuid_Extended_Topology_info(leaf);
 else if (leaf == 13)
  p = cpuid_Processor_Extended_States_info(leaf);
 else if (leaf == 15)
  p = cpuid_Quality_of_Service_info(leaf);
 else if (leaf == 0x80000002)
  p = cpuid_brand_part1_info(leaf);
 else if (leaf == 0x80000003)
  p = cpuid_brand_part2_info(leaf);
 else if (leaf == 0x80000004)
  p = cpuid_brand_part3_info(leaf);
 else
  p = cpuid(leaf);

 *eax = cpu_info[0];
 *ebx = cpu_info[1];
 *ecx = cpu_info[2];
 *edx = cpu_info[3];
}