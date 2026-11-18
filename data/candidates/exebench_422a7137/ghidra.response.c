void GetCPUInfo(int *cpu_info,int info_type)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int info_type_local;
  int *cpu_info_local;
  
  if (info_type == 0) {
    piVar1 = (int *)cpuid_basic_info(0);
  }
  else if (info_type == 1) {
    piVar1 = (int *)cpuid_Version_info(1);
  }
  else if (info_type == 2) {
    piVar1 = (int *)cpuid_cache_tlb_info(2);
  }
  else if (info_type == 3) {
    piVar1 = (int *)cpuid_serial_info(3);
  }
  else if (info_type == 4) {
    piVar1 = (int *)cpuid_Deterministic_Cache_Parameters_info(4);
  }
  else if (info_type == 5) {
    piVar1 = (int *)cpuid_MONITOR_MWAIT_Features_info(5);
  }
  else if (info_type == 6) {
    piVar1 = (int *)cpuid_Thermal_Power_Management_info(6);
  }
  else if (info_type == 7) {
    piVar1 = (int *)cpuid_Extended_Feature_Enumeration_info(7);
  }
  else if (info_type == 9) {
    piVar1 = (int *)cpuid_Direct_Cache_Access_info(9);
  }
  else if (info_type == 10) {
    piVar1 = (int *)cpuid_Architectural_Performance_Monitoring_info(10);
  }
  else if (info_type == 0xb) {
    piVar1 = (int *)cpuid_Extended_Topology_info(0xb);
  }
  else if (info_type == 0xd) {
    piVar1 = (int *)cpuid_Processor_Extended_States_info(0xd);
  }
  else if (info_type == 0xf) {
    piVar1 = (int *)cpuid_Quality_of_Service_info(0xf);
  }
  else if (info_type == -0x7ffffffe) {
    piVar1 = (int *)cpuid_brand_part1_info(0x80000002);
  }
  else if (info_type == -0x7ffffffd) {
    piVar1 = (int *)cpuid_brand_part2_info(0x80000003);
  }
  else if (info_type == -0x7ffffffc) {
    piVar1 = (int *)cpuid_brand_part3_info(0x80000004);
  }
  else {
    piVar1 = (int *)cpuid(info_type);
  }
  iVar2 = piVar1[1];
  iVar3 = piVar1[2];
  iVar4 = piVar1[3];
  *cpu_info = *piVar1;
  cpu_info[1] = iVar2;
  cpu_info[2] = iVar4;
  cpu_info[3] = iVar3;
  return;
}