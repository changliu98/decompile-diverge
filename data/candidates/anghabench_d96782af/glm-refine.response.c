0000153

double __cdecl rapl_dram_energy_units_probe(int model, double rapl_energy_units)
{
    // Check if the CPU model is in the range 128 to 132 (inclusive)
    if (model < 128 || model > 132)
        return rapl_energy_units;

    // Update the global energy unit and return the new value
    rapl_dram_energy_units = 0x3EF00B0FFE7AC4C2LL;
    return RAPL_DRAM_ENERGY_UNIT;
}