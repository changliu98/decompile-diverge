void computeRates(struct RateData *data, double *out_rates, void *unused) {
    // Calculate the absolute value of data->rate2 by clearing the sign bit
    double abs_rate2;
    uint64_t bits = *(uint64_t*)&data->rate2;
    bits ^= 0x8000000000000000ULL;
    abs_rate2 = *(double*)&bits;
    
    // out_rates[0] = abs(data->rate2) * 2.0
    out_rates[0] = abs_rate2 * 2.0;
    
    // out_rates[1] = data->rate1 * 2.0
    out_rates[1] = data->rate1 * 2.0;
}