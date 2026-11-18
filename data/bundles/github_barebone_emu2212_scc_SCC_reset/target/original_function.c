void
SCC_reset (SCC * scc)
{
  int i, j;

  if (scc == NULL)
    return;

  scc->mode = 0;
  scc->active = 0;
  scc->base_adr = 0x9000;

  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 5; j++)
      scc->wave[i][j] = 0;
    scc->count[i] = 0;
    scc->freq[i] = 0;
    scc->phase[i] = 0;
    scc->volume[i] = 0;
    scc->offset[i] = 0;
    scc->rotate[i] = 0;
    scc->ch_out[i] = 0;
  }

  memset(scc->reg,0,0x100-0xC0);

  scc->mask = 0;

  scc->ch_enable = 0xff;
  scc->ch_enable_next = 0xff;

  scc->cycle_4bit = 0;
  scc->cycle_8bit = 0;
  scc->refresh = 0;

  scc->out = 0;

  return;
}