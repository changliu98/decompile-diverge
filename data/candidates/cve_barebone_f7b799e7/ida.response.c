void __cdecl color_cmyk_to_rgb(opj_image_t *image)
{
  unsigned int i; // [rsp+8h] [rbp-38h]
  unsigned int ia; // [rsp+8h] [rbp-38h]
  unsigned int h; // [rsp+10h] [rbp-30h]
  unsigned int w; // [rsp+14h] [rbp-2Ch]
  float sK; // [rsp+18h] [rbp-28h]
  float sY; // [rsp+1Ch] [rbp-24h]
  float sM; // [rsp+20h] [rbp-20h]
  float sC; // [rsp+24h] [rbp-1Ch]
  float K; // [rsp+28h] [rbp-18h]
  float Y; // [rsp+2Ch] [rbp-14h]
  float M; // [rsp+30h] [rbp-10h]

  w = image->comps->w;
  h = image->comps->h;
  if ( image->numcomps >= 4 )
  {
    sC = 1.0 / (float)((1 << image->comps->prec) - 1);
    sM = 1.0 / (float)((1 << image->comps[1].prec) - 1);
    sY = 1.0 / (float)((1 << image->comps[2].prec) - 1);
    sK = 1.0 / (float)((1 << image->comps[3].prec) - 1);
    for ( i = 0; i < h * w; ++i )
    {
      M = 1.0 - (float)((float)image->comps[1].data[i] * sM);
      Y = 1.0 - (float)((float)image->comps[2].data[i] * sY);
      K = 1.0 - (float)((float)image->comps[3].data[i] * sK);
      image->comps->data[i] = (int)(float)((float)(255.0 * (float)(1.0 - (float)((float)image->comps->data[i] * sC))) * K);
      image->comps[1].data[i] = (int)(float)((float)(255.0 * M) * K);
      image->comps[2].data[i] = (int)(float)((float)(255.0 * Y) * K);
    }
    free(image->comps[3].data);
    image->comps[3].data = 0LL;
    image->comps->prec = 8;
    image->comps[1].prec = 8;
    image->comps[2].prec = 8;
    --image->numcomps;
    image->color_space = COLOR_SPACE::OPJ_CLRSPC_SRGB;
    for ( ia = 3; ia < image->numcomps; ++ia )
      memcpy(
        &image->comps[(unsigned __int64)ia],
        &image->comps[(unsigned __int64)(ia + 1)],
        sizeof(image->comps[(unsigned __int64)ia]));
  }
}