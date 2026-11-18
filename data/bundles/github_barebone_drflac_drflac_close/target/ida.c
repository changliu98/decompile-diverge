void __cdecl drflac_close(drflac *pFlac)
{
  if ( pFlac )
    drflac__free_from_callbacks(pFlac, &pFlac->allocationCallbacks);
}