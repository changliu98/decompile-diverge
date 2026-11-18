int exactO(double depth, double *temperature, double *melting_temperature, double *ice_heat_flux, double *bed_heat_flux, double *basal_melt_rate)
{
    // Calculate melting temperature Tm using constants
    *melting_temperature = DAT_00102040 * DAT_00102030 + DAT_00102038;
    
    // Calculate ice heat flux qice based on temperature difference and constant
    *ice_heat_flux = (DAT_00102020 * (DAT_00102028 - *melting_temperature)) / DAT_00102008;
    
    // Assign bed heat flux qbed from constant
    *bed_heat_flux = DAT_00102018;
    
    // Calculate basal melt rate bmelt using bed heat flux and ice heat flux
    *basal_melt_rate = (DAT_00102018 - *ice_heat_flux) / DAT_00102010;
    
    // Determine temperature TT based on depth z relative to threshold
    if (depth <= DAT_00102008) {
        if (depth < 0.0) {
            // For negative z, calculate TT using linear interpolation with offset
            *temperature = depth * DAT_00102048 + *melting_temperature;
        } else {
            // For non-negative z up to threshold, interpolate between Tm and max temperature
            *temperature = (DAT_00102028 - *melting_temperature) * (depth / DAT_00102008) + *melting_temperature;
        }
    } else {
        // For z beyond threshold, set TT to maximum temperature
        *temperature = DAT_00102028;
    }
    
    return 0;
}