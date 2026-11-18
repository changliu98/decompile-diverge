unsigned long pmc_sample_period(unsigned int base) {
    return (unsigned long)((unsigned long)__STACK_END - (unsigned long)base);
}