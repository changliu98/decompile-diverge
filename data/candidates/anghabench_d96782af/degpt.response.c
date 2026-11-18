double calculate_dram_energy_units(int cpu_model_id, double energy_unit_factor) {
    // Check if the model ID is within the range [0x80, 0x84]
    if (cpu_model_id - 0x80U < 5) {
        // Return a predefined constant value for specific models
        return DAT_00102008;
    }
    // Return the provided RAPL energy units for other models
    return energy_unit_factor;
}