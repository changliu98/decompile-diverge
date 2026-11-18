void drflac_close(void *ptr)
{
    struct drflac *flac = (drflac *)ptr;
    if (flac == ((void *)0))
        return;
    drflac_free_all(flac, &flac->allocationCallbacks);
    return;
}