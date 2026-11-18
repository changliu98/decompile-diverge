void drflac_close(struct drflac* pFlac) {
    if (pFlac != NULL) {
        drflac__free_from_callbacks(pFlac, (char*)pFlac + 0x10);
    }
}