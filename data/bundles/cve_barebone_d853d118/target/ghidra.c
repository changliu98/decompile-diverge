/* WARNING: Removing unreachable block (ram,0x00101f05) */
/* WARNING: Removing unreachable block (ram,0x00101f3b) */
/* WARNING: Removing unreachable block (ram,0x00101f48) */
/* WARNING: Removing unreachable block (ram,0x00101f52) */
/* WARNING: Removing unreachable block (ram,0x00101f2c) */
/* WARNING: Removing unreachable block (ram,0x00101f57) */

int imagetopnm(opj_image_t *image,char *outfile,int force_split)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  OPJ_UINT32 OVar4;
  uint uVar5;
  FILE *pFVar6;
  char *pcVar7;
  char *pcVar8;
  size_t sVar9;
  bool bVar10;
  int local_fc;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_d4;
  bool local_c2;
  size_t dotpos;
  size_t olen;
  char *tt;
  char *destname;
  char *tmp;
  FILE *fdest;
  int v;
  int prec;
  int triple;
  int has_alpha;
  int want_gray;
  int two;
  int fails;
  int adjustA;
  int adjustB;
  int adjustG;
  int adjustR;
  uint ncomp;
  uint compno;
  int i;
  int max;
  int hr;
  int wr;
  int *alpha;
  int *blue;
  int *green;
  int *red;
  int force_split_local;
  char *outfile_local;
  opj_image_t *image_local;
  int local_c;
  
  alpha = (int *)0x0;
  uVar1 = image->comps->prec;
  tmp = outfile;
  if ((int)uVar1 < 0x11) {
    for (; *tmp != '\0'; tmp = tmp + 1) {
    }
    bVar10 = true;
    if (tmp[-2] != 'g') {
      bVar10 = tmp[-2] == 'G';
    }
    ncomp = image->numcomps;
    if (bVar10) {
      ncomp = 1;
    }
    if ((force_split == 0) &&
       ((ncomp == 2 ||
        ((((2 < ncomp && (image->comps->dx == image->comps[1].dx)) &&
          (image->comps[1].dx == image->comps[2].dx)) &&
         (((image->comps->dy == image->comps[1].dy && (image->comps[1].dy == image->comps[2].dy)) &&
          ((image->comps->prec == image->comps[1].prec &&
           (image->comps[1].prec == image->comps[2].prec)))))))))) {
      pFVar6 = fopen(outfile,"wb");
      if (pFVar6 == (FILE *)0x0) {
        fprintf(*(FILE **)PTR_stderr_00104ff8,"ERROR -> failed to open %s for writing\n",outfile);
        local_c = 1;
      }
      else {
        bVar10 = 2 < ncomp;
        uVar2 = image->comps->w;
        uVar3 = image->comps->h;
        uVar5 = (1 << ((byte)uVar1 & 0x1f)) - 1;
        local_c2 = ncomp == 4 || ncomp == 2;
        red = image->comps->data;
        if (bVar10) {
          green = image->comps[1].data;
          blue = image->comps[2].data;
        }
        else {
          blue = (int *)0x0;
          green = (int *)0x0;
        }
        if (ncomp == 4 || ncomp == 2) {
          pcVar7 = "GRAYSCALE_ALPHA";
          if (bVar10) {
            pcVar7 = "RGB_ALPHA";
          }
          pcVar8 = opj_version();
          fprintf(pFVar6,
                  "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %u\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n"
                  ,pcVar8,(ulong)uVar2,(ulong)uVar3,(ulong)ncomp,uVar5,pcVar7);
          alpha = image->comps[ncomp - 1].data;
          if (image->comps[ncomp - 1].sgnd == 0) {
            local_d4 = 0;
          }
          else {
            local_d4 = 1 << ((char)image->comps[ncomp - 1].prec - 1U & 0x1f);
          }
          adjustA = local_d4;
        }
        else {
          pcVar7 = opj_version();
          fprintf(pFVar6,"P6\n# OpenJPEG-%s\n%d %d\n%d\n",pcVar7,(ulong)uVar2,(ulong)uVar3,
                  (ulong)uVar5);
          adjustA = 0;
        }
        if (image->comps->sgnd == 0) {
          local_e4 = 0;
        }
        else {
          local_e4 = 1 << ((char)image->comps->prec - 1U & 0x1f);
        }
        if (bVar10) {
          if (image->comps[1].sgnd == 0) {
            local_e8 = 0;
          }
          else {
            local_e8 = 1 << ((char)image->comps[1].prec - 1U & 0x1f);
          }
          adjustG = local_e8;
          if (image->comps[2].sgnd == 0) {
            local_ec = 0;
          }
          else {
            local_ec = 1 << ((char)image->comps[2].prec - 1U & 0x1f);
          }
          adjustB = local_ec;
        }
        else {
          adjustB = 0;
          adjustG = 0;
        }
        for (i = 0; i < (int)(uVar2 * uVar3); i = i + 1) {
          if ((int)uVar1 < 9) {
            v = *red;
            if (v < 0x100) {
              if (v < 0) {
                v = 0;
              }
            }
            else {
              v = 0xff;
            }
            fprintf(pFVar6,"%c",(ulong)(v & 0xff));
            if (bVar10) {
              v = *green;
              if (v < 0x100) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xff;
              }
              fprintf(pFVar6,"%c",(ulong)(v & 0xff));
              v = *blue;
              if (v < 0x100) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xff;
              }
              fprintf(pFVar6,"%c",(ulong)(v & 0xff));
              blue = blue + 1;
              green = green + 1;
            }
            if (local_c2) {
              v = *alpha;
              if (v < 0x100) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xff;
              }
              fprintf(pFVar6,"%c",(ulong)(v & 0xff));
              alpha = alpha + 1;
            }
          }
          else {
            v = *red + local_e4;
            if (v < 0x10000) {
              if (v < 0) {
                v = 0;
              }
            }
            else {
              v = 0xffff;
            }
            fprintf(pFVar6,"%c%c",(ulong)(v >> 8 & 0xff),(ulong)(v & 0xff));
            if (bVar10) {
              v = *green + adjustG;
              green = green + 1;
              if (v < 0x10000) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xffff;
              }
              fprintf(pFVar6,"%c%c",(ulong)(v >> 8 & 0xff),(ulong)(v & 0xff));
              v = *blue + adjustB;
              blue = blue + 1;
              if (v < 0x10000) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xffff;
              }
              fprintf(pFVar6,"%c%c",(ulong)(v >> 8 & 0xff),(ulong)(v & 0xff));
            }
            if (local_c2) {
              v = *alpha + adjustA;
              alpha = alpha + 1;
              if (v < 0x10000) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xffff;
              }
              fprintf(pFVar6,"%c%c",(ulong)(v >> 8 & 0xff),(ulong)(v & 0xff));
            }
          }
          red = red + 1;
        }
        fclose(pFVar6);
        local_c = 0;
      }
    }
    else {
      if (ncomp < image->numcomps) {
        fprintf(*(FILE **)PTR_stderr_00104ff8,"WARNING -> [PGM file] Only the first component\n");
        fprintf(*(FILE **)PTR_stderr_00104ff8,"           is written to the file\n");
      }
      sVar9 = strlen(outfile);
      pcVar7 = malloc(sVar9 + 8);
      if (pcVar7 == (char *)0x0) {
        fprintf(*(FILE **)PTR_stderr_00104ff8,"imagetopnm: memory out\n");
        local_c = 1;
      }
      else {
        for (compno = 0; compno < ncomp; compno = compno + 1) {
          if (ncomp < 2) {
            sprintf(pcVar7,"%s",outfile);
          }
          else {
            sVar9 = strlen(outfile);
            strncpy(pcVar7,outfile,sVar9 - 4);
            sprintf(pcVar7 + (sVar9 - 4),"_%u.pgm",(ulong)compno);
          }
          pFVar6 = fopen(pcVar7,"wb");
          if (pFVar6 == (FILE *)0x0) {
            fprintf(*(FILE **)PTR_stderr_00104ff8,"ERROR -> failed to open %s for writing\n",pcVar7)
            ;
            free(pcVar7);
            return 1;
          }
          uVar1 = image->comps[compno].w;
          uVar2 = image->comps[compno].h;
          OVar4 = image->comps[compno].prec;
          pcVar8 = opj_version();
          fprintf(pFVar6,"P5\n#OpenJPEG-%s\n%d %d\n%d\n",pcVar8,(ulong)uVar1,(ulong)uVar2,
                  (ulong)((1 << ((byte)OVar4 & 0x1f)) - 1));
          red = image->comps[compno].data;
          if (image->comps[compno].sgnd == 0) {
            local_fc = 0;
          }
          else {
            local_fc = 1 << ((char)image->comps[compno].prec - 1U & 0x1f);
          }
          if ((int)OVar4 < 9) {
            for (i = 0; i < (int)(uVar1 * uVar2); i = i + 1) {
              v = *red + local_fc;
              red = red + 1;
              if (v < 0x100) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xff;
              }
              fprintf(pFVar6,"%c",(ulong)(v & 0xff));
            }
          }
          else {
            for (i = 0; i < (int)(uVar1 * uVar2); i = i + 1) {
              v = *red + local_fc;
              red = red + 1;
              if (v < 0x10000) {
                if (v < 0) {
                  v = 0;
                }
              }
              else {
                v = 0xffff;
              }
              fprintf(pFVar6,"%c%c",(ulong)(v >> 8 & 0xff),(ulong)(v & 0xff));
            }
          }
          fclose(pFVar6);
        }
        free(pcVar7);
        local_c = 0;
      }
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00104ff8,
            "%s:%d:imagetopnm\n\tprecision %d is larger than 16\n\t: refused.\n","/work/harness.c",
            0xa1,(ulong)uVar1);
    local_c = 1;
  }
  return local_c;
}