double rapl_dram_energy_units_probe(int model,double rapl_energy_units)

{
  double rapl_energy_units_local;
  int model_local;
  double local_10;
  
  local_10 = rapl_energy_units;
  if (model - 0x80U < 5) {
    rapl_dram_energy_units = DAT_00102008;
    local_10 = DAT_00102008;
  }
  return local_10;
}