OPJ_BOOL opj_pi_next_rpcl(opj_pi_iterator_t *pi)

{
  OPJ_INT32 OVar1;
  OPJ_INT32 OVar2;
  OPJ_INT32 OVar3;
  OPJ_INT32 OVar4;
  uint uVar5;
  opj_pi_comp_t *poVar6;
  opj_pi_resolution_t *poVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  OPJ_UINT32 local_68;
  OPJ_UINT32 local_64;
  OPJ_INT32 prcj;
  OPJ_INT32 prci;
  OPJ_UINT32 rpy;
  OPJ_UINT32 rpx;
  OPJ_INT32 try1;
  OPJ_INT32 trx1;
  OPJ_INT32 try0;
  OPJ_INT32 trx0;
  OPJ_UINT32 levelno;
  OPJ_UINT32 dy;
  OPJ_UINT32 dx;
  OPJ_UINT32 resno;
  OPJ_UINT32 compno;
  OPJ_UINT32 index;
  opj_pi_resolution_t *res;
  opj_pi_comp_t *comp;
  opj_pi_iterator_t *pi_local;
  
  if (pi->first != 0) {
    pi->first = 0;
    pi->dx = 0;
    pi->dy = 0;
    for (compno = 0; compno < pi->numcomps; compno = compno + 1) {
      poVar6 = pi->comps + compno;
      for (resno = 0; resno < poVar6->numresolutions; resno = resno + 1) {
        local_64 = poVar6->dx *
                   (1 << (((char)poVar6->resolutions[resno].pdx + (char)poVar6->numresolutions + -1)
                          - (char)resno & 0x1fU));
        local_68 = poVar6->dy *
                   (1 << (((char)poVar6->resolutions[resno].pdy + (char)poVar6->numresolutions + -1)
                          - (char)resno & 0x1fU));
        if (pi->dx != 0) {
          local_64 = opj_uint_min(pi->dx,local_64);
        }
        pi->dx = local_64;
        if (pi->dy != 0) {
          local_68 = opj_uint_min(pi->dy,local_68);
        }
        pi->dy = local_68;
      }
    }
    if (pi->tp_on == '\0') {
      (pi->poc).ty0 = pi->ty0;
      (pi->poc).tx0 = pi->tx0;
      (pi->poc).ty1 = pi->ty1;
      (pi->poc).tx1 = pi->tx1;
    }
    pi->resno = (pi->poc).resno0;
    goto LAB_00101800;
  }
  do {
    pi->layno = pi->layno + 1;
    while ((pi->poc).layno1 <= pi->layno) {
      do {
        do {
          pi->compno = pi->compno + 1;
          while ((pi->poc).compno1 <= pi->compno) {
            pi->x = (pi->dx - pi->x % (int)pi->dx) + pi->x;
            while ((pi->poc).tx1 <= pi->x) {
              pi->y = (pi->dy - pi->y % (int)pi->dy) + pi->y;
              while ((pi->poc).ty1 <= pi->y) {
                pi->resno = pi->resno + 1;
LAB_00101800:
                if ((pi->poc).resno1 <= pi->resno) {
                  return 0;
                }
                pi->y = (pi->poc).ty0;
              }
              pi->x = (pi->poc).tx0;
            }
            pi->compno = (pi->poc).compno0;
          }
          poVar6 = pi->comps + pi->compno;
        } while (poVar6->numresolutions <= pi->resno);
        poVar7 = poVar6->resolutions + pi->resno;
        bVar8 = ((char)poVar6->numresolutions + -1) - (char)pi->resno;
        OVar1 = opj_int_ceildiv(pi->tx0,poVar6->dx << (bVar8 & 0x1f));
        OVar2 = opj_int_ceildiv(pi->ty0,poVar6->dy << (bVar8 & 0x1f));
        OVar3 = opj_int_ceildiv(pi->tx1,poVar6->dx << (bVar8 & 0x1f));
        OVar4 = opj_int_ceildiv(pi->ty1,poVar6->dy << (bVar8 & 0x1f));
        bVar9 = (char)poVar7->pdx + bVar8;
        bVar10 = (char)poVar7->pdy + bVar8;
      } while ((((pi->y % (int)(poVar6->dy << (bVar10 & 0x1f)) != 0) &&
                ((pi->y != pi->ty0 || ((OVar2 << (bVar8 & 0x1f)) % (1 << (bVar10 & 0x1f)) == 0))))
               || ((pi->x % (int)(poVar6->dx << (bVar9 & 0x1f)) != 0 &&
                   ((pi->x != pi->tx0 || ((OVar1 << (bVar8 & 0x1f)) % (1 << (bVar9 & 0x1f)) == 0))))
                  )) || ((poVar7->pw == 0 ||
                         (((poVar7->ph == 0 || (OVar1 == OVar3)) || (OVar2 == OVar4))))));
      OVar3 = opj_int_ceildiv(pi->x,poVar6->dx << (bVar8 & 0x1f));
      OVar3 = opj_int_floordivpow2(OVar3,poVar7->pdx);
      OVar1 = opj_int_floordivpow2(OVar1,poVar7->pdx);
      OVar4 = opj_int_ceildiv(pi->y,poVar6->dy << (bVar8 & 0x1f));
      OVar4 = opj_int_floordivpow2(OVar4,poVar7->pdy);
      OVar2 = opj_int_floordivpow2(OVar2,poVar7->pdy);
      pi->precno = (OVar3 - OVar1) + (OVar4 - OVar2) * poVar7->pw;
      pi->layno = (pi->poc).layno0;
    }
    uVar5 = pi->layno * pi->step_l + pi->resno * pi->step_r + pi->compno * pi->step_c +
            pi->precno * pi->step_p;
    if (pi->include[uVar5] == 0) {
      pi->include[uVar5] = 1;
      return 1;
    }
  } while( true );
}