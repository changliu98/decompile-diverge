int gdi_Bitmap_Decompress(gdiBitmapStruct* bitmapStruct, gdiBitmap* bitmap, void* srcData, int width, int height, int bpp, int compressedSize) {
    int status = 0;
    int srcFormat;
    int srcBytesPerPixel;
    int dstBytesPerPixel;
    int requiredSize;
    int rowSize;

    bitmap->field_10 = 0;
    bitmap->format = *(uint32_t*)bitmapStruct->field_0;
    
    rowSize = width * height;
    bitmap->scanlineSize = rowSize * GetBytesPerPixel(bitmap->format);
    bitmap->data = _aligned_malloc(bitmap->scanlineSize, 16);
    
    if (!bitmap->data) {
        return 0;
    }

    if (compressedSize != 0) {
        if (bpp < 32) {
            if (!interleaved_decompress(*(void**)bitmapStruct->field_8, srcData, compressedSize, width, height, bpp, bitmap->data, bitmap->format, 0, 0, 0, height, width, (char*)bitmapStruct->field_0 + 4)) {
                return 0;
            }
        } else {
            if (!planar_decompress(*(void**)((char*)bitmapStruct->field_8 + 8), srcData, compressedSize, width, height, bpp, bitmap->data, bitmap->format, 0, 0, 0, height, width, 1)) {
                return 0;
            }
        }
    } else {
        srcFormat = gdi_get_pixel_format(bpp);
        srcBytesPerPixel = GetBytesPerPixel(srcFormat);
        dstBytesPerPixel = GetBytesPerPixel(bitmap->format);
        
        if (srcBytesPerPixel == 0 || dstBytesPerPixel == 0) {
            return 0;
        }
        
        requiredSize = (compressedSize * dstBytesPerPixel) / srcBytesPerPixel;
        if ((uint32_t)requiredSize < bitmap->scanlineSize) {
            return 0;
        }
        
        if (!freerdp_image_copy(bitmap->data, bitmap->format, 0, 0, 0, width, height, srcData, srcFormat, 0, 0, 0, (char*)bitmapStruct->field_0 + 4, 1)) {
            return 0;
        }
    }

    return 1;
}