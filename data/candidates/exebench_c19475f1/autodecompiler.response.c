void cgi_store_get_action(SH2_struct *context)
{
   context->regs.SR.part.T = 4;
   context->cycles = 1;
}