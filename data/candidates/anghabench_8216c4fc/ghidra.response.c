uint create_ce_flags(uint stage)

{
  uint stage_local;
  
  return stage << ((byte)CE_STAGESHIFT & 0x1f);
}