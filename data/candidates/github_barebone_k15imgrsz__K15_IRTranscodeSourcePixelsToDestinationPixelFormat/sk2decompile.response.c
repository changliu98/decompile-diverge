void K15_IRTranscodeSourcePixelsToDestinationPixelFormat(
    K15_IRCameraDevice* device) {
  K15_IRSize width = device->width;
  K15_IRSize height = device->height;
  K15_IRPixel* sourcePixels = device->pixels;
  K15_IRPixelFormat sourcePixelFormat = device->pixelFormat;
  K15_IRPixelFormat destinationPixelFormat = device->destinationPixelFormat;
  if (sourcePixelFormat != destinationPixelFormat) {
    K15_IRPixel* destinationPixels =
        malloc(width * height *
               K15_IRPixelFormatSizeInBytes[destinationPixelFormat]);
    if (sourcePixelFormat == K15_IRPixelFormatR8 &&
        destinationPixelFormat == K15_IRPixelFormatR8G8) {
      K15_IRTranscodeFromR8ToR8G8(sourcePixels, destinationPixels, width,
                                  height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8) {
      K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, destinationPixels, width,
                                    height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8A8) {
      K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, destinationPixels, width,
                                      height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8 &&
               destinationPixelFormat == K15_IRPixelFormatR8) {
      K15_IRTranscodeFromR8G8ToR8(sourcePixels, destinationPixels, width,
                                  height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8) {
      K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, destinationPixels, width,
                                      height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8A8) {
      K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, destinationPixels, width,
                                        height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8 &&
               destinationPixelFormat == K15_IRPixelFormatR8) {
      K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, destinationPixels, width,
                                    height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8) {
      K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, destinationPixels, width,
                                      height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8A8) {
      K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, destinationPixels,
                                          width, height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8A8 &&
               destinationPixelFormat == K15_IRPixelFormatR8) {
      K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, destinationPixels, width,
                                      height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8A8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8) {
      K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, destinationPixels, width,
                                        height);
    } else if (sourcePixelFormat == K15_IRPixelFormatR8G8B8A8 &&
               destinationPixelFormat == K15_IRPixelFormatR8G8B8) {
      K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, destinationPixels,
                                          width, height);
    }
    device->destinationPixels = destinationPixels;
  }
}