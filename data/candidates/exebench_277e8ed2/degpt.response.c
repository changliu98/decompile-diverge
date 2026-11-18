void calc_sth11(float *humidity_ptr, float *temperature_ptr)
{
    // Calculate true temperature using linear approximation with calibration constants
    float true_temperature = *temperature_ptr * DAT_0010200c + DAT_00102020;
    
    // Calculate true relative humidity using polynomial compensation formula
    // based on measured humidity and true temperature
    float true_humidity = (true_temperature - DAT_00102010) * (*humidity_ptr * DAT_00102008 + DAT_0010200c) +
                    DAT_0010201c * *humidity_ptr * *humidity_ptr + DAT_00102018 * *humidity_ptr + DAT_00102014;
    
    // Clamp humidity to maximum allowed value (100%)
    if (DAT_00102004 < true_humidity) {
        true_humidity = DAT_00102004;
    }
    
    // Clamp humidity to minimum allowed value (0%)
    if ((double)true_humidity < DAT_00102028) {
        true_humidity = DAT_00102024;
    }
    
    // Update output parameters with calculated true temperature and humidity
    *temperature_ptr = true_temperature;
    *humidity_ptr = true_humidity;
}