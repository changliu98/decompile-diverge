void do_cpuid(uint *eax,uint *ebx,uint *ecx,uint *edx)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *edx_local;
  uint *ecx_local;
  uint *ebx_local;
  uint *eax_local;
  
  uVar1 = *eax;
  if (uVar1 == 0) {
    puVar2 = (uint *)cpuid_basic_info(0);
  }
  else if (uVar1 == 1) {
    puVar2 = (uint *)cpuid_Version_info(1);
  }
  else if (uVar1 == 2) {
    puVar2 = (uint *)cpuid_cache_tlb_info(2);
  }
  else if (uVar1 == 3) {
    puVar2 = (uint *)cpuid_serial_info(3);
  }
  else if (uVar1 == 4) {
    puVar2 = (uint *)cpuid_Deterministic_Cache_Parameters_info(4);
  }
  else if (uVar1 == 5) {
    puVar2 = (uint *)cpuid_MONITOR_MWAIT_Features_info(5);
  }
  else if (uVar1 == 6) {
    puVar2 = (uint *)cpuid_Thermal_Power_Management_info(6);
  }
  else if (uVar1 == 7) {
    puVar2 = (uint *)cpuid_Extended_Feature_Enumeration_info(7);
  }
  else if (uVar1 == 9) {
    puVar2 = (uint *)cpuid_Direct_Cache_Access_info(9);
  }
  else if (uVar1 == 10) {
    puVar2 = (uint *)cpuid_Architectural_Performance_Monitoring_info(10);
  }
  else if (uVar1 == 0xb) {
    puVar2 = (uint *)cpuid_Extended_Topology_info(0xb);
  }
  else if (uVar1 == 0xd) {
    puVar2 = (uint *)cpuid_Processor_Extended_States_info(0xd);
  }
  else if (uVar1 == 0xf) {
    puVar2 = (uint *)cpuid_Quality_of_Service_info(0xf);
  }
  else if (uVar1 == 0x80000002) {
    puVar2 = (uint *)cpuid_brand_part1_info(0x80000002);
  }
  else if (uVar1 == 0x80000003) {
    puVar2 = (uint *)cpuid_brand_part2_info(0x80000003);
  }
  else if (uVar1 == 0x80000004) {
    puVar2 = (uint *)cpuid_brand_part3_info(0x80000004);
  }
  else {
    puVar2 = (uint *)cpuid(uVar1);
  }
  uVar1 = puVar2[1];
  uVar3 = puVar2[2];
  uVar4 = puVar2[3];
  *eax = *puVar2;
  *ebx = uVar1;
  *ecx = uVar4;
  *edx = uVar3;
  return;
}