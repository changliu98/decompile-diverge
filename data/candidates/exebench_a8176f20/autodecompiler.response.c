static unsigned char btcl_reg(unsigned int reg_in, int bitno, unsigned int *reg_out_p)
{
    unsigned char carry;
    unsigned int reg_out;

    __asm__ __volatile__("pushf\n\t"
                         "btc %2, %1\n\t"
                         "setc %0\n\t"
                         "popf\n\t"
                         : "=r"(carry), "=r"(reg_out)
                         : "r"(reg_in), "c"(bitno));
    *reg_out_p = reg_out;
    return carry;
}