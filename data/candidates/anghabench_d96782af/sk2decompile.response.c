static double rapl_dram_energy_units_probe(int rapl_dram_energy_unit) {
  double rapl_dram_energy_units;
  switch (rapl_dram_energy_unit) {
    case RAPL_UNIT_JOULES:
    case RAPL_UNIT_MILLIJOULES:
    case RAPL_UNIT_MICROJOULES:
    case RAPL_UNIT_NANOJOULES:
    case RAPL_UNIT_PICOJOULES:
      rapl_dram_energy_units = 0.0000153;
      break;
    default:
      rapl_dram_energy_units = 1.0;
      break;
  }
  return rapl_dram_energy_units;
}