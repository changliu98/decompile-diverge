OPJ_BOOL __cdecl opj_pi_next_rpcl(opj_pi_iterator_t *pi)
{
  OPJ_INT32 v1; // edi
  OPJ_INT32 v2; // edi
  OPJ_INT32 v4; // [rsp+8h] [rbp-68h]
  OPJ_INT32 v5; // [rsp+Ch] [rbp-64h]
  OPJ_UINT32 v6; // [rsp+10h] [rbp-60h]
  int v7; // [rsp+14h] [rbp-5Ch]
  OPJ_INT32 prci; // [rsp+1Ch] [rbp-54h]
  OPJ_UINT32 rpy; // [rsp+20h] [rbp-50h]
  OPJ_UINT32 rpx; // [rsp+24h] [rbp-4Ch]
  OPJ_INT32 try1; // [rsp+28h] [rbp-48h]
  OPJ_INT32 trx1; // [rsp+2Ch] [rbp-44h]
  OPJ_INT32 try0; // [rsp+30h] [rbp-40h]
  OPJ_INT32 trx0; // [rsp+34h] [rbp-3Ch]
  OPJ_UINT32 levelno; // [rsp+38h] [rbp-38h]
  int dy; // [rsp+3Ch] [rbp-34h]
  OPJ_UINT32 resno; // [rsp+44h] [rbp-2Ch]
  OPJ_UINT32 compno; // [rsp+48h] [rbp-28h]
  OPJ_UINT32 index; // [rsp+4Ch] [rbp-24h]
  opj_pi_resolution_t *res; // [rsp+50h] [rbp-20h]
  opj_pi_resolution_t *resa; // [rsp+50h] [rbp-20h]
  opj_pi_comp_t *comp; // [rsp+58h] [rbp-18h]
  opj_pi_comp_t *compa; // [rsp+58h] [rbp-18h]

  if ( !pi->first )
    goto LABEL_43;
  pi->first = 0;
  pi->dx = 0;
  pi->dy = 0;
  for ( compno = 0; compno < pi->numcomps; ++compno )
  {
    comp = &pi->comps[compno];
    for ( resno = 0; resno < comp->numresolutions; ++resno )
    {
      res = &comp->resolutions[resno];
      dy = (1 << (LOBYTE(comp->numresolutions) + LOBYTE(res->pdy) - 1 - resno)) * comp->dy;
      if ( pi->dx )
        v7 = opj_uint_min(pi->dx, (1 << (LOBYTE(comp->numresolutions) + LOBYTE(res->pdx) - 1 - resno)) * comp->dx);
      else
        v7 = (1 << (LOBYTE(comp->numresolutions) + LOBYTE(res->pdx) - 1 - resno)) * comp->dx;
      pi->dx = v7;
      if ( pi->dy )
        v6 = opj_uint_min(pi->dy, dy);
      else
        v6 = dy;
      pi->dy = v6;
    }
  }
  if ( !pi->tp_on )
  {
    pi->poc.ty0 = pi->ty0;
    pi->poc.tx0 = pi->tx0;
    pi->poc.ty1 = pi->ty1;
    pi->poc.tx1 = pi->tx1;
  }
  for ( pi->resno = pi->poc.resno0; pi->resno < pi->poc.resno1; ++pi->resno )
  {
    for ( pi->y = pi->poc.ty0; pi->y < pi->poc.ty1; pi->y += pi->dy - pi->y % (signed int)pi->dy )
    {
      for ( pi->x = pi->poc.tx0; pi->x < pi->poc.tx1; pi->x += pi->dx - pi->x % (signed int)pi->dx )
      {
        for ( pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; ++pi->compno )
        {
          compa = &pi->comps[pi->compno];
          if ( pi->resno < compa->numresolutions )
          {
            resa = &compa->resolutions[pi->resno];
            levelno = compa->numresolutions - 1 - pi->resno;
            trx0 = opj_int_ceildiv(pi->tx0, compa->dx << levelno);
            try0 = opj_int_ceildiv(pi->ty0, compa->dy << levelno);
            trx1 = opj_int_ceildiv(pi->tx1, compa->dx << levelno);
            try1 = opj_int_ceildiv(pi->ty1, compa->dy << levelno);
            rpx = levelno + resa->pdx;
            rpy = levelno + resa->pdy;
            if ( (!(pi->y % (signed int)(compa->dy << rpy)) || pi->y == pi->ty0 && (try0 << levelno) % (1 << rpy))
              && (!(pi->x % (signed int)(compa->dx << rpx)) || pi->x == pi->tx0 && (trx0 << levelno) % (1 << rpx))
              && resa->pw
              && resa->ph
              && trx0 != trx1
              && try0 != try1 )
            {
              v1 = opj_int_ceildiv(pi->x, compa->dx << levelno);
              v4 = opj_int_floordivpow2(v1, resa->pdx);
              prci = v4 - opj_int_floordivpow2(trx0, resa->pdx);
              v2 = opj_int_ceildiv(pi->y, compa->dy << levelno);
              v5 = opj_int_floordivpow2(v2, resa->pdy);
              pi->precno = resa->pw * (v5 - opj_int_floordivpow2(try0, resa->pdy)) + prci;
              for ( pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; ++pi->layno )
              {
                index = pi->step_p * pi->precno
                      + pi->step_c * pi->compno
                      + pi->step_r * pi->resno
                      + pi->step_l * pi->layno;
                if ( !pi->include[index] )
                {
                  pi->include[index] = 1;
                  return 1;
                }
LABEL_43:
                ;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}