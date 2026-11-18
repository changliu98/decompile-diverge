int div_dbl(struct div_t *res, unsigned long long divisor) {
    if (divisor == 0 || res->rem >= divisor) {
        return 1;
    }
    
    unsigned long long dividend = res->quot;
    unsigned long long remainder = res->rem;
    
    res->quot = dividend / divisor;
    res->rem = dividend % divisor;
    
    return 0;
}