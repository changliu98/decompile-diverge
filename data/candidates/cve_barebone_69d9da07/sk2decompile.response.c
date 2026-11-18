OPJ_BOOL opj_pi_next_rpcl(opj_pi_iterator_t* pi) {
  if (!pi->first) {
    return 0;
  }
  pi->first = 0;
  pi->min_dx = 0;
  pi->min_dy = 0;
  OPJ_UINT32 i, j;
  for (j = 0; j < pi->numresolutions; j++) {
    opj_pi_resolution_t* res = &pi->resolutions[j];
    for (i = 0; i < res->numcomps; i++) {
      opj_pi_comp_t* comp = &res->comps[i];
      OPJ_UINT32 dx = res->dx * (1 << (comp->dw + res->numcomps - 1 - i));
      OPJ_UINT32 dy = res->dy * (1 << (comp->dh + res->numcomps - 1 - i));
      pi->min_dx = pi->min_dx ? opj_uint_min(pi->min_dx, dx) : dx;
      pi->min_dy = pi->min_dy ? opj_uint_min(pi->min_dy, dy) : dy;
    }
  }
  if (!pi->full_tile_size) {
    pi->tile.x0 = pi->x0;
    pi->tile.y0 = pi->y0;
    pi->tile.x1 = pi->x1;
    pi->tile.y1 = pi->y1;
  }
  for (pi->c = pi->tile.c0; pi->c < pi->tile.c1; pi->c++) {
    for (pi->x = pi->tile.x0; pi->x < pi->tile.x1;
         pi->x += pi->min_dx - pi->x % pi->min_dx) {
      for (pi->y = pi->tile.y0; pi->y < pi->tile.y1;
           pi->y += pi->min_dy - pi->y % pi->min_dy) {
        for (pi->r = pi->tile.r0; pi->r < pi->tile.r1; pi->r++) {
          opj_pi_resolution_t* res = &pi->resolutions[pi->r];
          if (pi->c < res->numcomps) {
            opj_pi_comp_t* comp = &res->comps[pi->c];
            OPJ_UINT32 shift = res->numcomps - 1 - pi->c;
            OPJ_UINT32 y_div =
                opj_int_ceildiv(pi->y, res->dy << shift);
            OPJ_UINT32 x_div =
                opj_int_ceildiv(pi->x, res->dx << shift);
            OPJ_UINT32 y1_div =
                opj_int_ceildiv(pi->tile.y1, res->dy << shift);
            OPJ_UINT32 x1_div =
                opj_int_ceildiv(pi->tile.x1, res->dx << shift);
            OPJ_UINT32 dh = comp->dh + shift;
            OPJ_UINT32 dw = comp->dw + shift;
            if ((pi->x % (res->dx << dw) != 0) ||
                (pi->x == pi->x0 && (x_div << shift) % (1 << dw) != 0)) {
              continue;
            }
            if ((pi->y % (res->dy << dh) != 0) ||
                (pi->y == pi->y0 && (y_div << shift) % (1 << dh) != 0)) {
              continue;
            }
            if (comp->nx == 0 || comp->ny == 0) {
              continue;
            }
            if (y_div == y1_div || x_div == x1_div) {
              continue;
            }
            OPJ_UINT32 y_comp =
                opj_int_floordivpow2(opj_int_ceildiv(pi->y, res->dy << shift),
                                     comp->dh) -
                opj_int_floordivpow2(y_div, comp->dh);
            OPJ_UINT32 x_comp =
                opj_int_floordivpow2(opj_int_ceildiv(pi->x, res->dx << shift),
                                     comp->dw) -
                opj_int_floordivpow2(x_div, comp->dw);
            pi->comp_index = y_comp * comp->nx + x_comp;
            for (pi->p = pi->tile.p0; pi->p < pi->tile.p1; pi->p++) {
              OPJ_UINT32 index = pi->p_stride * pi->comp_index +
                                 pi->r_stride * pi->r + pi->c_stride * pi->c +
                                 pi->t_stride * pi->p;
              if (!pi->visited[index]) {
                pi->visited[index] = 1;
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}