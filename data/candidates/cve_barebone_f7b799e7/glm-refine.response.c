void __cdecl color_cmyk_to_rgb(opj_image_t *image)
{
  unsigned int i, j;
  unsigned int h, w, num_pixels;
  float sK, sY, sM, sC;
  float K, Y, M, C;

  // Assuming standard OpenJPEG structures, image->comps is an array.
  // Note: The original decompilation accesses image->comps->w directly,
  // implying it might be an inline array or single component context.
  w = image->comps->w;
  h = image->comps->h;

  if (image->numcomps >= 4)
  {
    // Precompute scale factors based on bit depth (precision)
    sC = 1.0f / (float)((1 << image->comps[0].prec) - 1);
    sM = 1.0f / (float)((1 << image->comps[1].prec) - 1);
    sY = 1.0f / (float)((1 << image->comps[2].prec) - 1);
    sK = 1.0f / (float)((1 << image->comps[3].prec) - 1);

    num_pixels = h * w;
    for (i = 0; i < num_pixels; ++i)
    {
      // Normalize CMYK values to [0.0, 1.0] and invert (C -> R, M -> G, Y -> B)
      M = 1.0f - (float)image->comps[1].data[i] * sM;
      Y = 1.0f - (float)image->comps[2].data[i] * sY;
      K = 1.0f - (float)image->comps[3].data[i] * sK;
      C = 1.0f - (float)image->comps[0].data[i] * sC;

      // Apply Key (Black) scaling and map back to 0-255 range
      image->comps[0].data[i] = (int)(255.0f * C * K);
      image->comps[1].data[i] = (int)(255.0f * M * K);
      image->comps[2].data[i] = (int)(255.0f * Y * K);
    }

    // Free the Key (Black) component as it's no longer needed
    free(image->comps[3].data);
    image->comps[3].data = NULL;

    // Update remaining components to 8-bit depth
    image->comps[0].prec = 8;
    image->comps[1].prec = 8;
    image->comps[2].prec = 8;

    // Decrement component count and switch color space to sRGB
    --image->numcomps;
    image->color_space = COLOR_SPACE::OPJ_CLRSPC_SRGB;

    // Shift any remaining components (index > 3) down by 1 to fill the gap
    for (j = 3; j < image->numcomps; ++j)
    {
      memcpy(&image->comps[j], &image->comps[j + 1], sizeof(image->comps[j]));
    }
  }
}