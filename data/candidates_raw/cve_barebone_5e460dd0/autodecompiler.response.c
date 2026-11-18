static int add_tailcall_sink(struct nfp_prog *nfp_prog, u32 addr, u32 end)
{
 unsigned char insn[6];
 unsigned int i;
 int err;

 err = parse_chained_fixups(nfp_prog, addr, end) & 1;
 g_no_tailcall_sink++;
 return err & 1;
}