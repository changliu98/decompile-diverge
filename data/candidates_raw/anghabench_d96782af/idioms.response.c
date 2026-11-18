double rapl_rapl_get_rapl_energy_units(int model, int family)
{
  switch (model) {
  case 0x80:
  case 0x81:
  case 0x82:
  case 0x83:
  case 0x84:
    rapl_dram_energy_units = 1.111e-12;
    return 1.111e-12;
  default:
    return rapl_energy_units;
  }
}