void cpuid(uint op,uint *eax,uint *ebx,uint *ecx,uint *edx)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *edx_local;
  uint *ecx_local;
  uint *ebx_local;
  uint *eax_local;
  uint op_local;
  
  if (op == 0) {
    puVar1 = (uint *)cpuid_basic_info(0);
  }
  else if (op == 1) {
    puVar1 = (uint *)cpuid_Version_info(1);
  }
  else if (op == 2) {
    puVar1 = (uint *)cpuid_cache_tlb_info(2);
  }
  else if (op == 3) {
    puVar1 = (uint *)cpuid_serial_info(3);
  }
  else if (op == 4) {
    puVar1 = (uint *)cpuid_Deterministic_Cache_Parameters_info(4);
  }
  else if (op == 5) {
    puVar1 = (uint *)cpuid_MONITOR_MWAIT_Features_info(5);
  }
  else if (op == 6) {
    puVar1 = (uint *)cpuid_Thermal_Power_Management_info(6);
  }
  else if (op == 7) {
    puVar1 = (uint *)cpuid_Extended_Feature_Enumeration_info(7);
  }
  else if (op == 9) {
    puVar1 = (uint *)cpuid_Direct_Cache_Access_info(9);
  }
  else if (op == 10) {
    puVar1 = (uint *)cpuid_Architectural_Performance_Monitoring_info(10);
  }
  else if (op == 0xb) {
    puVar1 = (uint *)cpuid_Extended_Topology_info(0xb);
  }
  else if (op == 0xd) {
    puVar1 = (uint *)cpuid_Processor_Extended_States_info(0xd);
  }
  else if (op == 0xf) {
    puVar1 = (uint *)cpuid_Quality_of_Service_info(0xf);
  }
  else if (op == 0x80000002) {
    puVar1 = (uint *)cpuid_brand_part1_info(0x80000002);
  }
  else if (op == 0x80000003) {
    puVar1 = (uint *)cpuid_brand_part2_info(0x80000003);
  }
  else if (op == 0x80000004) {
    puVar1 = (uint *)cpuid_brand_part3_info(0x80000004);
  }
  else {
    puVar1 = (uint *)cpuid(op);
  }
  uVar2 = puVar1[1];
  uVar3 = puVar1[2];
  uVar4 = puVar1[3];
  *eax = *puVar1;
  *ebx = uVar2;
  *ecx = uVar4;
  *edx = uVar3;
  return;
}