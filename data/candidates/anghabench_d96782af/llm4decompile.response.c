double rapl_dram_energy_units_probe(int model, double rapl_energy_units) {
  switch (model) {
    case INTEL_FAM10_BROADWELL_X:
    case INTEL_FAM10_XEON_PHI_KNL:
    case INTEL_FAM10_XEON_PHI_KNM:
    case INTEL_FAM10_ATOM_SILVERMONT_X:
    case INTEL_FAM10_CORE_BROADWELL_X:
      rapl_dram_energy_units = 15.3 / 1000000;
      break;
    default:
      break;
  }
  return rapl_energy_units;
}