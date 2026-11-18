unsigned long long pmc_sample_period(unsigned int counter_value) {
    return COUNTER_OVERFLOW - counter_value;
}