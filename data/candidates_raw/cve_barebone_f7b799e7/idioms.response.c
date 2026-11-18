void opj_image_decompress(struct opj_image_t *image)
{
  unsigned int i;
  unsigned int w = image->comps[0].w;
  unsigned int h = image->comps[0].h;
  if (image->numcomps >= 4)
  {
    float sC = 1.0 / (float)(1 << (image->comps[0].prec - 1));
    float sM = 1.0 / (float)(1 << (image->comps[1].prec - 1));
    float sY = 1.0 / (float)(1 << (image->comps[2].prec - 1));
    float sK = 1.0 / (float)(1 << (image->comps[3].prec - 1));
    for (i = 0; i < w * h; i++)
    {
      float C = 1.0 - sC * (float)image->comps[0].data[i];
      float M = 1.0 - sM * (float)image->comps[1].data[i];
      float Y = 1.0 - sY * (float)image->comps[2].data[i];
      float K = 1.0 - sK * (float)image->comps[3].data[i];
      image->comps[0].data[i] = (unsigned char)(255 * K * C);
      image->comps[1].data[i] = (unsigned char)(255 * K * M);
      image->comps[2].data[i] = (unsigned char)(255 * K * Y);
    }
    opj_image_free(image->comps[3].data);
    image->comps[3].data = ((void *)0);
    image->comps[0].prec = 8;
    image->comps[1].prec = 8;
    image->comps[2].prec = 8;
    image->numcomps -= 1;
    image->color_space = OPJ_CLRSPC_SRGB;
    for (i = 3; i < image->numcomps; i++)
    {
      opj_image_move(&image->comps[i], &image->comps[i + 1],
        sizeof(opj_image_comp_t));
    }
  }
}