static void SH2rotcl(SH2_struct * sh)
{
   sh->regs.SR.part.T = (u32)sh->regs.SR.part.T >> 1;
}