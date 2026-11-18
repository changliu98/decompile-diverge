double
rapl_dram_energy_units_probe(int  model, double rapl_energy_units)
{
	/* only called for genuine_intel, family 6 */

	switch (model) {
	case INTEL_FAM6_HASWELL_X:	/* HSX */
	case INTEL_FAM6_BROADWELL_X:	/* BDX */
	case INTEL_FAM6_BROADWELL_XEON_D:	/* BDX-DE */
	case INTEL_FAM6_XEON_PHI_KNL:	/* KNL */
	case INTEL_FAM6_XEON_PHI_KNM:
		return (rapl_dram_energy_units = 15.3 / 1000000);
	default:
		return (rapl_energy_units);
	}
}