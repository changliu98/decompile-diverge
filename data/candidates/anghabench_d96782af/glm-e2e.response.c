double rapl_dram_energy_units_probe(uint32_t cpu_model, double energy_units) {
    if (cpu_model - 0x80 <= 4) {
        rapl_dram_energy_units = 15.3;
        return 15.3;
    } else {
        return energy_units;
    }
}