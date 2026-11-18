void jpq_cpuid_custom(int CPUInfo[4], int InfoType){
  int j, i;
  int info[4];
  if (InfoType == 0){
    info[0] = cpuid_basic_info(0)[0];
    info[1] = cpuid_basic_info(0)[1];
    info[2] = cpuid_basic_info(0)[2];
    info[3] = cpuid_basic_info(0)[3];
  } else if (InfoType == 1){
    info[0] = cpuid_Version_info(1)[0];
    info[1] = cpuid_Version_info(1)[1];
    info[2] = cpuid_Version_info(1)[2];
    info[3] = cpuid_Version_info(1)[3];
  } else if (InfoType == 2){
    info[0] = cpuid_cache_tlb_info(2)[0];
    info[1] = cpuid_cache_tlb_info(2)[1];
    info[2] = cpuid_cache_tlb_info(2)[2];
    info[3] = cpuid_cache_tlb_info(2)[3];
  } else if (InfoType == 3){
    info[0] = cpuid_serial_info(3)[0];
    info[1] = cpuid_serial_info(3)[1];
    info[2] = cpuid_serial_info(3)[2];
    info[3] = cpuid_serial_info(3)[3];
  } else if (InfoType == 4){
    info[0] = cpuid_Deterministic_Cache_Parameters_info(4)[0];
    info[1] = cpuid_Deterministic_Cache_Parameters_info(4)[1];
    info[2] = cpuid_Deterministic_Cache_Parameters_info(4)[2];
    info[3] = cpuid_Deterministic_Cache_Parameters_info(4)[3];
  } else if (InfoType == 5){
    info[0] = cpuid_MONITOR_MWAIT_Features_info(5)[0];
    info[1] = cpuid_MONITOR_MWAIT_Features_info(5)[1];
    info[2] = cpuid_MONITOR_MWAIT_Features_info(5)[2];
    info[3] = cpuid_MONITOR_MWAIT_Features_info(5)[3];
  } else if (InfoType == 6){
    info[0] = cpuid_Thermal_Power_Management_info(6)[0];
    info[1] = cpuid_Thermal_Power_Management_info(6)[1];
    info[2] = cpuid_Thermal_Power_Management_info(6)[2];
    info[3] = cpuid_Thermal_Power_Management_info(6)[3];
  } else if (InfoType == 7){
    info[0] = cpuid_Extended_Feature_Enumeration_info(7)[0];
    info[1] = cpuid_Extended_Feature_Enumeration_info(7)[1];
    info[2] = cpuid_Extended_Feature_Enumeration_info(7)[2];
    info[3] = cpuid_Extended_Feature_Enumeration_info(7)[3];
  } else if (InfoType == 9){
    info[0] = cpuid_Direct_Cache_Access_info(9)[0];
    info[1] = cpuid_Direct_Cache_Access_info(9)[1];
    info[2] = cpuid_Direct_Cache_Access_info(9)[2];
    info[3] = cpuid_Direct_Cache_Access_info(9)[3];
  } else if (InfoType == 10){
    info[0] = cpuid_Architectural_Performance_Monitoring_info(10)[0];
    info[1] = cpuid_Architectural_Performance_Monitoring_info(10)[1];
    info[2] = cpuid_Architectural_Performance_Monitoring_info(10)[2];
    info[3] = cpuid_Architectural_Performance_Monitoring_info(10)[3];
  } else if (InfoType == 11){
    info[0] = cpuid_Extended_Topology_info(11)[0];
    info[1] = cpuid_Extended_Topology_info(11)[1];
    info[2] = cpuid_Extended_Topology_info(11)[2];
    info[3] = cpuid_Extended_Topology_info(11)[3];
  } else if (InfoType == 13){
    info[0] = cpuid_Processor_Extended_States_info(13)[0];
    info[1] = cpuid_Processor_Extended_States_info(13)[1];
    info[2] = cpuid_Processor_Extended_States_info(13)[2];
    info[3] = cpuid_Processor_Extended_States_info(13)[3];
  } else if (InfoType == 15){
    info[0] = cpuid_Quality_of_Service_info(15)[0];
    info[1] = cpuid_Quality_of_Service_info(15)[1];
    info[2] = cpuid_Quality_of_Service_info(15)[2];
    info[3] = cpuid_Quality_of_Service_info(15)[3];
  } else if (InfoType == 0x80000002){
    info[0] = cpuid_brand_part1_info(0x80000002)[0];
    info[1] = cpuid_brand_part1_info(0x80000002)[1];
    info[2] = cpuid_brand_part1_info(0x80000002)[2];
    info[3] = cpuid_brand_part1_info(0x80000002)[3];
  } else if (InfoType == 0x80000003){
    info[0] = cpuid_brand_part2_info(0x80000003)[0];
    info[1] = cpuid_brand_part2_info(0x80000003)[1];
    info[2] = cpuid_brand_part2_info(0x80000003)[2];
    info[3] = cpuid_brand_part2_info(0x80000003)[3];
  } else if (InfoType == 0x80000004){
    info[0] = cpuid_brand_part3_info(0x80000004)[0];
    info[1] = cpuid_brand_part3_info(0x80000004)[1];
    info[2] = cpuid_brand_part3_info(0x80000004)[2];
    info[3] = cpuid_brand_part3_info(0x80000004)[3];
  } else {
    info[0] = cpuid(InfoType)[0];
    info[1] = cpuid(InfoType)[1];
    info[2] = cpuid(InfoType)[2];
    info[3] = cpuid(InfoType)[3];
  }
  for (j=0; j<4; j++){
    CPUInfo[j] = info[j];
  }
}