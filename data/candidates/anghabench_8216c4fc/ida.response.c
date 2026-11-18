unsigned int __cdecl create_ce_flags(unsigned int stage)
{
  return stage << CE_STAGESHIFT;
}