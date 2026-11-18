void _K15_IRTranscodeSourcePixelsToDestinationPixelFormat(struct K15_IRImageContext* context) {
    int width = context->width;
    int height = context->height;
    void* sourcePixels = context->pixels;
    int sourceFormat = context->sourcePixelFormat;
    int destFormat = context->destinationPixelFormat;

    if (sourceFormat != destFormat) {
        int size = width * height * kir_format_to_byte_lut[destFormat];
        void* transcodedPixels = malloc(size);

        if (sourceFormat == 0 && destFormat == 1) {
            _K15_IRTranscodeFromR8ToR8G8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 0 && destFormat == 2) {
            _K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 0 && destFormat == 3) {
            _K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 1 && destFormat == 0) {
            _K15_IRTranscodeFromR8G8ToR8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 1 && destFormat == 2) {
            _K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 1 && destFormat == 3) {
            _K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 2 && destFormat == 0) {
            _K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 2 && destFormat == 1) {
            _K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 2 && destFormat == 3) {
            _K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 3 && destFormat == 0) {
            _K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 3 && destFormat == 1) {
            _K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, transcodedPixels, width, height);
        } else if (sourceFormat == 3 && destFormat == 2) {
            _K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, transcodedPixels, width, height);
        }

        context->transcodedPixels = transcodedPixels;
    }
}