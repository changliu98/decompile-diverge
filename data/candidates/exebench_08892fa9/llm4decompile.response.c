void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
 uint32_t cpu_info[4];

 if (leaf == 0) {
  cpu_info[0] = cpuid_basic_info(leaf)[0];
  cpu_info[1] = cpuid_basic_info(leaf)[1];
  cpu_info[2] = cpuid_basic_info(leaf)[2];
  cpu_info[3] = cpuid_basic_info(leaf)[3];
 } else if (leaf == 1) {
  cpu_info[0] = cpuid_Version_info(leaf)[0];
  cpu_info[1] = cpuid_Version_info(leaf)[1];
  cpu_info[2] = cpuid_Version_info(leaf)[2];
  cpu_info[3] = cpuid_Version_info(leaf)[3];
 } else if (leaf == 2) {
  cpu_info[0] = cpuid_cache_tlb_info(leaf)[0];
  cpu_info[1] = cpuid_cache_tlb_info(leaf)[1];
  cpu_info[2] = cpuid_cache_tlb_info(leaf)[2];
  cpu_info[3] = cpuid_cache_tlb_info(leaf)[3];
 } else if (leaf == 3) {
  cpu_info[0] = cpuid_serial_info(leaf)[0];
  cpu_info[1] = cpuid_serial_info(leaf)[1];
  cpu_info[2] = cpuid_serial_info(leaf)[2];
  cpu_info[3] = cpuid_serial_info(leaf)[3];
 } else if (leaf == 4) {
  cpu_info[0] = cpuid_Deterministic_Cache_Parameters_info(leaf)[0];
  cpu_info[1] = cpuid_Deterministic_Cache_Parameters_info(leaf)[1];
  cpu_info[2] = cpuid_Deterministic_Cache_Parameters_info(leaf)[2];
  cpu_info[3] = cpuid_Deterministic_Cache_Parameters_info(leaf)[3];
 } else if (leaf == 5) {
  cpu_info[0] = cpuid_MONITOR_MWAIT_Features_info(leaf)[0];
  cpu_info[1] = cpuid_MONITOR_MWAIT_Features_info(leaf)[1];
  cpu_info[2] = cpuid_MONITOR_MWAIT_Features_info(leaf)[2];
  cpu_info[3] = cpuid_MONITOR_MWAIT_Features_info(leaf)[3];
 } else if (leaf == 6) {
  cpu_info[0] = cpuid_Thermal_Power_Management_info(leaf)[0];
  cpu_info[1] = cpuid_Thermal_Power_Management_info(leaf)[1];
  cpu_info[2] = cpuid_Thermal_Power_Management_info(leaf)[2];
  cpu_info[3] = cpuid_Thermal_Power_Management_info(leaf)[3];
 } else if (leaf == 7) {
  cpu_info[0] = cpuid_Extended_Feature_Enumeration_info(leaf)[0];
  cpu_info[1] = cpuid_Extended_Feature_Enumeration_info(leaf)[1];
  cpu_info[2] = cpuid_Extended_Feature_Enumeration_info(leaf)[2];
  cpu_info[3] = cpuid_Extended_Feature_Enumeration_info(leaf)[3];
 } else if (leaf == 9) {
  cpu_info[0] = cpuid_Direct_Cache_Access_info(leaf)[0];
  cpu_info[1] = cpuid_Direct_Cache_Access_info(leaf)[1];
  cpu_info[2] = cpuid_Direct_Cache_Access_info(leaf)[2];
  cpu_info[3] = cpuid_Direct_Cache_Access_info(leaf)[3];
 } else if (leaf == 10) {
  cpu_info[0] = cpuid_Architectural_Performance_Monitoring_info(leaf)[0];
  cpu_info[1] = cpuid_Architectural_Performance_Monitoring_info(leaf)[1];
  cpu_info[2] = cpuid_Architectural_Performance_Monitoring_info(leaf)[2];
  cpu_info[3] = cpuid_Architectural_Performance_Monitoring_info(leaf)[3];
 } else if (leaf == 11) {
  cpu_info[0] = cpuid_Extended_Topology_info(leaf)[0];
  cpu_info[1] = cpuid_Extended_Topology_info(leaf)[1];
  cpu_info[2] = cpuid_Extended_Topology_info(leaf)[2];
  cpu_info[3] = cpuid_Extended_Topology_info(leaf)[3];
 } else if (leaf == 13) {
  cpu_info[0] = cpuid_Processor_Extended_States_info(leaf)[0];
  cpu_info[1] = cpuid_Processor_Extended_States_info(leaf)[1];
  cpu_info[2] = cpuid_Processor_Extended_States_info(leaf)[2];
  cpu_info[3] = cpuid_Processor_Extended_States_info(leaf)[3];
 } else if (leaf == 15) {
  cpu_info[0] = cpuid_Quality_of_Service_info(leaf)[0];
  cpu_info[1] = cpuid_Quality_of_Service_info(leaf)[1];
  cpu_info[2] = cpuid_Quality_of_Service_info(leaf)[2];
  cpu_info[3] = cpuid_Quality_of_Service_info(leaf)[3];
 } else if (leaf == 0x80000002) {
  cpu_info[0] = cpuid_brand_part1_info(leaf)[0];
  cpu_info[1] = cpuid_brand_part1_info(leaf)[1];
  cpu_info[2] = cpuid_brand_part1_info(leaf)[2];
  cpu_info[3] = cpuid_brand_part1_info(leaf)[3];
 } else if (leaf == 0x80000003) {
  cpu_info[0] = cpuid_brand_part2_info(leaf)[0];
  cpu_info[1] = cpuid_brand_part2_info(leaf)[1];
  cpu_info[2] = cpuid_brand_part2_info(leaf)[2];
  cpu_info[3] = cpuid_brand_part2_info(leaf)[3];
 } else if (leaf == 0x80000004) {
  cpu_info[0] = cpuid_brand_part3_info(leaf)[0];
  cpu_info[1] = cpuid_brand_part3_info(leaf)[1];
  cpu_info[2] = cpuid_brand_part3_info(leaf)[2];
  cpu_info[3] = cpuid_brand_part3_info(leaf)[3];
 } else {
  cpu_info[0] = cpuid(leaf)[0];
  cpu_info[1] = cpuid(leaf)[1];
  cpu_info[2] = cpuid(leaf)[2];
  cpu_info[3] = cpuid(leaf)[3];
 }

 *eax = cpu_info[0];
 *ebx = cpu_info[1];
 *ecx = cpu_info[2];
 *edx = cpu_info[3];
}