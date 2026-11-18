int __cdecl cfftp_comp_twiddle(cfftp_plan *plan)
{
    size_t length = plan->length;
    cfftp_cmplx *twid = (cfftp_cmplx *)malloc(16 * length); // 16 bytes = 2 * sizeof(double)
    
    if (!twid)
        return -1;

    sincos_2pibyn(length, (double *)twid);

    size_t l1 = 1;
    size_t memofs = 0;

    for (size_t k = 0; k < plan->nfct; ++k)
    {
        cfftp_factor *fct = &plan->fct[k];
        size_t ip = fct->fct;
        size_t ido = length / (ip * l1);

        // Assign twiddle factor pointer and advance memory offset
        fct->tw = &plan->mem[memofs];
        memofs += (ido - 1) * (ip - 1);

        // Populate standard twiddle factors
        for (size_t j = 1; j < ip; ++j)
        {
            for (size_t i = 1; i < ido; ++i)
            {
                size_t twid_idx = i * l1 * j;
                fct->tw[(i - 1) + (ido - 1) * (j - 1)] = twid[twid_idx];
            }
        }

        // Populate special twiddle factors if the factor is large (> 11)
        if (ip > 11)
        {
            fct->tws = &plan->mem[memofs];
            memofs += ip;

            for (size_t j = 0; j < ip; ++j)
            {
                size_t twid_idx = ido * l1 * j;
                fct->tws[j] = twid[twid_idx];
            }
        }

        l1 *= ip;
    }

    free(twid);
    return 0;
}