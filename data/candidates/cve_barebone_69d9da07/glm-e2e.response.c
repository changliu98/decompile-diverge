int opj_pi_next_rpcl(struct opj_pi_iterator *pi) {
    if (!pi->first) {
        return 0;
    }
    pi->first = 0;
    pi->dx_min = 0;
    pi->dy_min = 0;

    for (uint32_t compno = 0; compno < pi->num_comps2; compno++) {
        struct opj_pi_comp *comp = &pi->comps[compno];
        for (uint32_t resno = 0; resno < comp->numresolutions; resno++) {
            struct opj_pi_resolution *res = &comp->resolutions[resno];
            int dx = comp->dx * (1 << (comp->numresolutions - 1 - resno));
            int dy = comp->dy * (1 << (comp->numresolutions - 1 - resno));
            
            if (pi->dx_min == 0) {
                pi->dx_min = dx;
            } else {
                pi->dx_min = opj_uint_min(pi->dx_min, dx);
            }
            
            if (pi->dy_min == 0) {
                pi->dy_min = dy;
            } else {
                pi->dy_min = opj_uint_min(pi->dy_min, dy);
            }
        }
    }

    if (!pi->pad0) {
        pi->tx1 = pi->y1;
        pi->tx0 = pi->y0;
        pi->ty1 = pi->x1;
        pi->ty0 = pi->x0;
    }

    pi->resno = pi->num_layers; // Likely a typo in original source: should be pi->num_comps or similar, but matches assembly

    for (; pi->resno < pi->max_resno; pi->resno++) {
        pi->py = pi->tx1;
        for (; pi->py < pi->ty1; pi->py += pi->dy_min) {
            pi->px = pi->tx0;
            for (; pi->px < pi->ty0; pi->px += pi->dx_min) { // Note: original assembly uses ty0 here
                pi->compno = pi->num_layers; // Again, likely a typo in original source
                
                for (; pi->compno < pi->max_compno; pi->compno++) {
                    struct opj_pi_comp *comp = &pi->comps[pi->compno];
                    if (pi->resno >= comp->numresolutions) {
                        continue;
                    }
                    struct opj_pi_resolution *res = &comp->resolutions[pi->resno];
                    int level_shift = comp->numresolutions - 1 - pi->resno;
                    int trx0 = opj_int_ceildiv(pi->tx0, comp->dx << level_shift);
                    int try0 = opj_int_ceildiv(pi->ty0, comp->dy << level_shift);
                    int trx1 = opj_int_ceildiv(pi->tx1, comp->dx << level_shift);
                    int try1 = opj_int_ceildiv(pi->ty1, comp->dy << level_shift);
                    int rpx = res->dx + level_shift;
                    int rpy = res->dy + level_shift;
                    
                    if (!((pi->py % (comp->dy << rpy)) == 0 && (pi->py == pi->ty0 || ((try0 << level_shift) % (1 << rpy)) == 0))) {
                        continue;
                    }
                    if (!((pi->px % (comp->dx << rpx)) == 0 && (pi->px == pi->tx0 || ((trx0 << level_shift) % (1 << rpx)) == 0))) {
                        continue;
                    }
                    if (res->num_precincts_x == 0 || res->num_precincts_y == 0) {
                        continue;
                    }
                    if (trx0 == trx1 || try0 == try1) {
                        continue;
                    }
                    
                    int prec_y = opj_int_floordivpow2(opj_int_ceildiv(pi->py, comp->dx << level_shift), res->dx) - 
                                 opj_int_floordivpow2(trx0, res->dx);
                    int prec_x = opj_int_floordivpow2(opj_int_ceildiv(pi->px, comp->dy << level_shift), res->dy) - 
                                 opj_int_floordivpow2(try0, res->dy);
                    pi->precno = prec_x + prec_y * res->num_precincts_x;
                    
                    for (pi->layno = pi->dx; pi->layno < pi->max_precno; pi->layno++) {
                        int index = pi->layno * pi->step_l + pi->resno * pi->step_r + 
                                    pi->compno * pi->step_c + pi->precno * pi->step_p;
                        if (pi->include[index] == 0) {
                            pi->include[index] = 1;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}