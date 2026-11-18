void advance_spos(SPosState *spos) 
{
    // Each counter is incremented by 1 and wraps around its respective modulus.
    // The use of prime moduli (43, 47, 51, 53, 59) indicates a deterministic 
    // sequence with a massive combined period before the entire state repeats.
    spos->counter0 = (spos->counter0 + 1) % 43;
    spos->counter1 = (spos->counter1 + 1) % 47;
    spos->counter2 = (spos->counter2 + 1) % 51;
    spos->counter3 = (spos->counter3 + 1) % 53;
    spos->counter4 = (spos->counter4 + 1) % 59;
}