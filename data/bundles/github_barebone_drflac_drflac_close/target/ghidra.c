void drflac_close(drflac *pFlac)

{
  drflac *pFlac_local;
  
  if (pFlac != (drflac *)0x0) {
    drflac__free_from_callbacks(pFlac,&pFlac->allocationCallbacks);
  }
  return;
}