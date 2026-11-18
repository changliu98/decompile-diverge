void SCC_reset (SCC *scc)
{
  int c, r ;

  if (scc == NULL) return ;

  scc->mode = scc->recv_clk = scc->recv_clk_old = 0 ;
  scc->recv_data = 0x9000 ;

  for (c = 0 ; c < 6 ; c++)
  {
    for (r = 0 ; r < 6 ; r++) scc->reg[c][r] = 0 ;
    scc->freq[c] = scc->freq_old[c] = 0 ;
    scc->freq_cnt[c] = scc->freq_cnt_old[c] = 0 ;
    scc->freq_res[c] = scc->freq_res_old[c] = 0 ;
    scc->out[c] = 0 ;
    scc->out_old[c] = 0 ;
    scc->out_cnt[c] = 0 ;
  }

  memset(scc->wave, 0, sizeof(scc->wave)) ;

  scc->irq = 0 ;
  scc->irq_mask = 0xff ;
  scc->irq_out = 0xff ;
  scc->irq_enable = 0 ;
  scc->irq_line = 0 ;
  scc->irq_pending = 0 ;
  scc->irq_vector = 0 ;

  scc->mask = 0 ;
}