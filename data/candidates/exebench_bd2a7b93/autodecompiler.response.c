static void bmp_iter_next(SH2_struct * sh)
{
   sh->regs.SR.part.T = (u32)sh->regs.SR.part.T >> 1;
}