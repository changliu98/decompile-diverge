/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void color_cmyk_to_rgb(opj_image_t *image)

{
  OPJ_UINT32 OVar1;
  OPJ_UINT32 OVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  uint i;
  uint max;
  uint h;
  uint w;
  float sK;
  float sY;
  float sM;
  float sC;
  float K;
  float Y;
  float M;
  float C;
  opj_image_t *image_local;
  
  OVar1 = image->comps->w;
  OVar2 = image->comps->h;
  if (3 < image->numcomps) {
    fVar3 = DAT_00102004 / (float)((1 << ((byte)image->comps->prec & 0x1f)) + -1);
    fVar4 = DAT_00102004 / (float)((1 << ((byte)image->comps[1].prec & 0x1f)) + -1);
    fVar5 = DAT_00102004 / (float)((1 << ((byte)image->comps[2].prec & 0x1f)) + -1);
    fVar6 = DAT_00102004 / (float)((1 << ((byte)image->comps[3].prec & 0x1f)) + -1);
    for (i = 0; i < OVar1 * OVar2; i = i + 1) {
      fVar7 = DAT_00102004 - (float)image->comps[1].data[i] * fVar4;
      fVar8 = DAT_00102004 - (float)image->comps[2].data[i] * fVar5;
      fVar9 = DAT_00102004 - (float)image->comps[3].data[i] * fVar6;
      image->comps->data[i] =
           (int)(_DAT_00102008 * (DAT_00102004 - (float)image->comps->data[i] * fVar3) * fVar9);
      image->comps[1].data[i] = (int)(_DAT_00102008 * fVar7 * fVar9);
      image->comps[2].data[i] = (int)(_DAT_00102008 * fVar8 * fVar9);
    }
    free(image->comps[3].data);
    image->comps[3].data = (OPJ_INT32 *)0x0;
    image->comps->prec = 8;
    image->comps[1].prec = 8;
    image->comps[2].prec = 8;
    image->numcomps = image->numcomps - 1;
    image->color_space = OPJ_CLRSPC_SRGB;
    for (i = 3; i < image->numcomps; i = i + 1) {
      memcpy(image->comps + i,image->comps + (i + 1),0x40);
    }
  }
  return;
}