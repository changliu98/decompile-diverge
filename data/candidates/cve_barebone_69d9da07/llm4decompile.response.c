OPJ_BOOL opj_pi_next_rpcl(opj_pi_iterator_t *pi)
{
    OPJ_UINT32 index;
    opj_pi_resolution_t *res;
    opj_pi_comp_t *comp;
    OPJ_UINT32 resno;
    OPJ_UINT32 compno;
    OPJ_UINT32 dx, dy;
    OPJ_UINT32 levelno;
    OPJ_UINT32 rpx, rpy;
    OPJ_INT32 trx0, try0, trx1, try1;
    OPJ_INT32 prci, prcj;
    OPJ_UINT32 pw, ph;
    OPJ_UINT32 numcomps;
    OPJ_UINT32 numresos;
    OPJ_UINT32 numlayers;
    OPJ_UINT32 numprecincts;
    OPJ_UINT32 numl;
    OPJ_UINT32 numr;
    OPJ_UINT32 numc;
    OPJ_UINT32 nump;
    OPJ_UINT32 i, j;

    if (pi->first) {
        pi->first = 0;
        pi->dx = 0;
        pi->dy = 0;
        for (compno = 0; compno < pi->numcomps; compno++) {
            comp = &pi->comps[compno];
            for (resno = 0; resno < comp->numresolutions; resno++) {
                res = &comp->resolutions[resno];
                dx = comp->dx * (1 << (comp->numresolutions - 1 - resno + res->pdx));
                dy = comp->dy * (1 << (comp->numresolutions - 1 - resno + res->pdy));
                if (pi->dx) {
                    pi->dx = opj_uint_min(pi->dx, dx);
                } else {
                    pi->dx = dx;
                }
                if (pi->dy) {
                    pi->dy = opj_uint_min(pi->dy, dy);
                } else {
                    pi->dy = dy;
                }
            }
        }
        if (!pi->tp_on) {
            pi->poc.tx0 = pi->tx0;
            pi->poc.ty0 = pi->ty0;
            pi->poc.tx1 = pi->tx1;
            pi->poc.ty1 = pi->ty1;
        }
        pi->resno = pi->poc.resno0;
        return opj_pi_next_rpcl(pi);
    }

    while (1) {
        pi->layno++;
        if (pi->layno < pi->poc.layno1) {
            index = pi->layno * pi->step_l + pi->resno * pi->step_r +
                    pi->compno * pi->step_c + pi->precno * pi->step_p;
            if (!pi->include[index]) {
                pi->include[index] = 1;
                return 1;
            }
            continue;
        }

        pi->compno++;
        if (pi->compno < pi->poc.compno1) {
            continue;
        }

        comp = &pi->comps[pi->compno];
        if (pi->resno < comp->numresolutions) {
            res = &comp->resolutions[pi->resno];
            numresos = comp->numresolutions - 1 - pi->resno;
            trx0 = opj_int_ceildiv(pi->tx0, comp->dx << numresos);
            try0 = opj_int_ceildiv(pi->ty0, comp->dy << numresos);
            trx1 = opj_int_ceildiv(pi->tx1, comp->dx << numresos);
            try1 = opj_int_ceildiv(pi->ty1, comp->dy << numresos);
            pw = res->pw;
            ph = res->ph;
            if ((pi->y % (comp->dy << (numresos + res->pdy)) &&
                    (pi->y != pi->ty0 || !(try0 << numresos % (1 << (numresos + res->pdy))))) ||
                    (pi->x % (comp->dx << (numresos + res->pdx)) &&
                     (pi->x != pi->tx0 || !(trx0 << numresos % (1 << (numresos + res->pdx))))) ||
                    (!pw || !ph || trx0 == trx1 || try0 == try1)) {
                continue;
            }
            prci = opj_int_floordivpow2(opj_int_ceildiv(pi->x, comp->dx << numresos), res->pdx) -
                   opj_int_floordivpow2(trx0, res->pdx);
            prcj = opj_int_floordivpow2(opj_int_ceildiv(pi->y, comp->dy << numresos), res->pdy) -
                   opj_int_floordivpow2(try0, res->pdy);
            pi->precno = prci + prcj * pw;
            pi->layno = pi->poc.layno0;
            continue;
        }

        pi->x += pi->dx - pi->x % pi->dx;
        if (pi->x < pi->poc.tx1) {
            continue;
        }

        pi->y += pi->dy - pi->y % pi->dy;
        if (pi->y < pi->poc.ty1) {
            pi->x = pi->poc.tx0;
            continue;
        }

        pi->resno++;
        if (pi->resno < pi->poc.resno1) {
            pi->y = pi->poc.ty0;
            pi->x = pi->poc.tx0;
            continue;
        }

        return 0;
    }
}