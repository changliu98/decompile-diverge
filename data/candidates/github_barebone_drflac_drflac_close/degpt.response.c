void drflac_close(drflac *flacDecoder)
{
    // Check if the FLAC decoder instance is valid before proceeding
    if (flacDecoder) {
        // Free the resources associated with the FLAC decoder using its custom allocation callbacks
        drflac__free_from_callbacks(flacDecoder, &flacDecoder->allocationCallbacks);
    }
}