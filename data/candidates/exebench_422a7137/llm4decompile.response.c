void GetCPUInfo(int *cpu_info, int info_type){

  int i;
  int *info;

  if(info_type==0)
    info=cpuid_basic_info(info_type);
  else if(info_type==1)
    info=cpuid_Version_info(info_type);
  else if(info_type==2)
    info=cpuid_cache_tlb_info(info_type);
  else if(info_type==3)
    info=cpuid_serial_info(info_type);
  else if(info_type==4)
    info=cpuid_Deterministic_Cache_Parameters_info(info_type);
  else if(info_type==5)
    info=cpuid_MONITOR_MWAIT_Features_info(info_type);
  else if(info_type==6)
    info=cpuid_Thermal_Power_Management_info(info_type);
  else if(info_type==7)
    info=cpuid_Extended_Feature_Enumeration_info(info_type);
  else if(info_type==9)
    info=cpuid_Direct_Cache_Access_info(info_type);
  else if(info_type==10)
    info=cpuid_Architectural_Performance_Monitoring_info(info_type);
  else if(info_type==11)
    info=cpuid_Extended_Topology_info(info_type);
  else if(info_type==13)
    info=cpuid_Processor_Extended_States_info(info_type);
  else if(info_type==15)
    info=cpuid_Quality_of_Service_info(info_type);
  else if(info_type==0x80000002)
    info=cpuid_brand_part1_info(info_type);
  else if(info_type==0x80000003)
    info=cpuid_brand_part2_info(info_type);
  else if(info_type==0x80000004)
    info=cpuid_brand_part3_info(info_type);
  else
    info=cpuid(info_type);

  for(i=0;i<4;i++)
    cpu_info[i]=info[i];

}