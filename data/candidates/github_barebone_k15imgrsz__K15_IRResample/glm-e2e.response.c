int _K15_IRResample(void* pContext) {
    // Context struct field offsets (deduced from assembly):
    // 0x08: pSourceImageData
    // 0x10: pDestImageData
    // 0x18: pTempImageData (optional, falls back to pSourceImageData)
    // 0x20: method (0 = Nearest, 1 = Bilinear, 2 = Bicubic)
    // 0x24: format
    // 0x2c: bytesPerPixel (index into LUT)
    // 0x30: srcPitch
    // 0x34: srcWidth
    // 0x38: srcHeight
    // 0x3c: destWidth
    // 0x40: destHeight

    int method               = *(int*)((char*)pContext + 0x24);
    int format               = *(int*)((char*)pContext + 0x20);
    
    void* pTempSource = *(void**)((char*)pContext + 0x18);
    if (!pTempSource) {
        pTempSource = *(void**)((char*)pContext + 0x08);
    }
    
    void* pDest               = *(void**)((char*)pContext + 0x10);
    int destWidth             = *(int*)((char*)pContext + 0x3c);
    int destHeight            = *(int*)((char*)pContext + 0x40);
    int srcHeight             = *(int*)((char*)pContext + 0x38);
    int srcWidth              = *(int*)((char*)pContext + 0x34);
    int srcPitch              = *(int*)((char*)pContext + 0x30);
    int bytesPerPixelIndex    = *(int*)((char*)pContext + 0x2c);
    
    int bytesPerPixel         = kir_format_to_byte_lut[bytesPerPixelIndex];
    int destSize              = destWidth * destHeight * bytesPerPixel;
    
    memset(pDest, 0, destSize);

    if (method == 0) {
        _K15_IRSampleNearestNeighbour(
            pTempSource, 
            pDest, 
            srcWidth, 
            srcHeight, 
            destWidth, 
            destHeight, 
            bytesPerPixelIndex
        );
    } else if (method == 1 || method == 2) {
        int tempWidth = destWidth;
        int tempHeight = srcHeight;
        int tempBytesPerPixelIndex = bytesPerPixelIndex;
        int tempBytesPerPixel = kir_format_to_byte_lut[tempBytesPerPixelIndex];
        int tempSize = tempWidth * tempHeight * tempBytesPerPixel;
        
        void* pTempBuffer = malloc(tempSize);
        memset(pTempBuffer, 0, tempSize);
        
        if (method == 1) {
            // Bilinear
            _K15_IRHorizontallySampleBilinear(
                pTempSource, 
                pTempBuffer, 
                (unsigned short)srcWidth, 
                (unsigned short)srcHeight, 
                (unsigned short)tempWidth, 
                (unsigned short)tempHeight, 
                srcPitch, 
                srcPitch
            );
            
            tempWidth = srcWidth;
            tempHeight = destHeight;
            destWidth = *(int*)((char*)pContext + 0x40);
            destHeight = *(int*)((char*)pContext + 0x3c);
            
            _K15_IRHorizontallySampleBilinear(
                pTempBuffer, 
                pDest, 
                (unsigned short)tempWidth, 
                (unsigned short)tempHeight, 
                (unsigned short)destWidth, 
                (unsigned short)destHeight, 
                srcPitch, 
                srcPitch
            );
        } else if (method == 2) {
            // Bicubic
            _K15_IRHorizontallySampleBicubic(
                pTempSource, 
                pTempBuffer, 
                (unsigned short)srcWidth, 
                (unsigned short)srcHeight, 
                (unsigned short)tempWidth, 
                (unsigned short)tempHeight, 
                srcPitch, 
                srcPitch
            );
            
            tempWidth = srcWidth;
            tempHeight = destHeight;
            destWidth = *(int*)((char*)pContext + 0x40);
            destHeight = *(int*)((char*)pContext + 0x3c);
            
            _K15_IRHorizontallySampleBicubic(
                pTempBuffer, 
                pDest, 
                (unsigned short)tempWidth, 
                (unsigned short)tempHeight, 
                (unsigned short)destWidth, 
                (unsigned short)destHeight, 
                srcPitch, 
                srcPitch
            );
        }
    }

    return 0;
}