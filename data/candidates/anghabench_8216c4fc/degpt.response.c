uint create_ce_flags(uint stageIndex)
{
  // Shift the stage value left by the lower 5 bits of CE_STAGESHIFT
  // to create the CE flags.
  return stageIndex << ((byte)CE_STAGESHIFT & 0x1f);
}