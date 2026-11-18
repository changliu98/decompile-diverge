gdImage *gdImageCreateFromTgaCtx(gdIOCtx *ctx) {
    int pixel_index = 0;
    oTga *tga = NULL;
    gdImage *image = NULL;
    int x = 0;
    int y = 0;
    int *row = NULL;
    int alpha_val;

    tga = (oTga *)gdMalloc(0x38);
    if (tga == NULL) {
        return NULL;
    }

    tga->pixels = NULL;
    // The assembly zeroes out offset 0x28, which likely corresponds to another pointer/field.
    *(void **)((char *)tga + 0x28) = NULL; 

    if (read_header_tga(ctx, tga) < 0) {
        free_tga(tga);
        return NULL;
    }

    if (read_image_tga(ctx, tga) < 0) {
        free_tga(tga);
        return NULL;
    }

    image = gdImageCreateTrueColor(tga->width, tga->height);
    if (image == NULL) {
        free_tga(tga);
        return NULL;
    }

    if (tga->alphabits != 0) {
        gdImageAlphaBlending(image, 0);
        gdImageSaveAlpha(image, 1);
    }

    for (y = 0; y < tga->height; y++) {
        row = image->tpixels[y];
        for (x = 0; x < tga->width; x++) {
            if (tga->bpp == 24) {
                *row = (tga->pixels[pixel_index + 2] << 16) |
                       (tga->pixels[pixel_index + 1] << 8) |
                       tga->pixels[pixel_index];
                pixel_index += 3;
            } else if (tga->bpp == 32 || tga->alphabits != 0) {
                alpha_val = tga->pixels[pixel_index + 3];
                *row = ((0x7f - (alpha_val >> 1)) << 24) |
                       (tga->pixels[pixel_index + 2] << 16) |
                       (tga->pixels[pixel_index + 1] << 8) |
                       tga->pixels[pixel_index];
                pixel_index += 4;
            }
            row++;
        }
    }

    if (tga->flipv != 0 && tga->fliph != 0) {
        gdImageFlipBoth(image);
    } else if (tga->flipv != 0) {
        gdImageFlipVertical(image);
    } else if (tga->fliph != 0) {
        gdImageFlipHorizontal(image);
    }

    free_tga(tga);
    return image;
}