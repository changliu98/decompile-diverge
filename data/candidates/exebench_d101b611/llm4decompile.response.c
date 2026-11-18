int and_peep2_q(int val, int *peep)
{
    *peep = val & 0xfe;
    return val;
}