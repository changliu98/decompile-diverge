double __cdecl rapl_dram_energy_units_probe(int model, double rapl_energy_units)
{
  if ( (unsigned int)(model - 128) > 4 )
    return rapl_energy_units;
  rapl_dram_energy_units = 0x3EF00B0FFE7AC4C2LL;
  return 0.0000153;
}