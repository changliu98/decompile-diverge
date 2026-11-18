void cpuinfo(int code,int *eax,int *ebx,int *ecx,int *edx)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *edx_local;
  int *ecx_local;
  int *ebx_local;
  int *eax_local;
  int code_local;
  
  if (code == 0) {
    piVar1 = (int *)cpuid_basic_info(0);
  }
  else if (code == 1) {
    piVar1 = (int *)cpuid_Version_info(1);
  }
  else if (code == 2) {
    piVar1 = (int *)cpuid_cache_tlb_info(2);
  }
  else if (code == 3) {
    piVar1 = (int *)cpuid_serial_info(3);
  }
  else if (code == 4) {
    piVar1 = (int *)cpuid_Deterministic_Cache_Parameters_info(4);
  }
  else if (code == 5) {
    piVar1 = (int *)cpuid_MONITOR_MWAIT_Features_info(5);
  }
  else if (code == 6) {
    piVar1 = (int *)cpuid_Thermal_Power_Management_info(6);
  }
  else if (code == 7) {
    piVar1 = (int *)cpuid_Extended_Feature_Enumeration_info(7);
  }
  else if (code == 9) {
    piVar1 = (int *)cpuid_Direct_Cache_Access_info(9);
  }
  else if (code == 10) {
    piVar1 = (int *)cpuid_Architectural_Performance_Monitoring_info(10);
  }
  else if (code == 0xb) {
    piVar1 = (int *)cpuid_Extended_Topology_info(0xb);
  }
  else if (code == 0xd) {
    piVar1 = (int *)cpuid_Processor_Extended_States_info(0xd);
  }
  else if (code == 0xf) {
    piVar1 = (int *)cpuid_Quality_of_Service_info(0xf);
  }
  else if (code == -0x7ffffffe) {
    piVar1 = (int *)cpuid_brand_part1_info(0x80000002);
  }
  else if (code == -0x7ffffffd) {
    piVar1 = (int *)cpuid_brand_part2_info(0x80000003);
  }
  else if (code == -0x7ffffffc) {
    piVar1 = (int *)cpuid_brand_part3_info(0x80000004);
  }
  else {
    piVar1 = (int *)cpuid(code);
  }
  iVar2 = piVar1[1];
  iVar3 = piVar1[2];
  iVar4 = piVar1[3];
  *eax = *piVar1;
  *ebx = iVar2;
  *ecx = iVar4;
  *edx = iVar3;
  return;
}