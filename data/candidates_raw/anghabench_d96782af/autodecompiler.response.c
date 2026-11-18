static double rapl_get_energy_units(int model, double default_units) {
  double units;
  switch(model) {
    case 0x1A:
    case 0x1E:
    case 0x2A:
    case 0x2E:
      rapl_dram_energy_units = 0.5e-9;
      units = 0.5e-9;
      break;
    default:
      units = default_units;
  }
  return units;
}