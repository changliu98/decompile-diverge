void drflac_close(drflac *pFlac)
{
    if (pFlac != NULL) {
        drflac__free_from_callbacks(pFlac, &pFlac->allocationCallbacks);
    }
}