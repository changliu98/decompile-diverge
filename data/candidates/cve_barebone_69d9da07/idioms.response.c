int opj_pi_next_rpcl(struct opj_pi_iterator *pi)
{
   struct opj_pi_comp *comp;
   struct opj_pi_resolution *res;
   unsigned int compno;
   unsigned int resno;
   int dy;
   int dx;
   int pdy;
   int pdx;
   int levelno;
   int rpy;
   int rpx;
   int try0; int try1;
   int trx0; int trx1;
   int prci; int prci1; int prci0;
   int prcy; int prcy1; int prcy0;
   unsigned int index;
   if (pi->first == 0)
      return 0;
   pi->first = 0;
   pi->dx = 0;
   pi->dy = 0;
   for (compno = 0; compno < pi->numcomps; compno++)
   {
      comp = &pi->comps[compno];
      for (resno = 0; resno < comp->numresolutions; resno++)
      {
         res = &comp->resolutions[resno];
         dy = comp->dy * (1 << (comp->numresolutions - 1 - resno - res->pdy));
         if (pi->dx == 0)
            dx = comp->dx * (1 << (comp->numresolutions - 1 - resno - res->pdx));
         else
            dx = opj_pi_min(pi->dx, comp->dx * (1 << (comp->numresolutions - 1 - resno - res->pdx)));
         pi->dx = dx;
         if (pi->dy == 0)
            dy = comp->dy * (1 << (comp->numresolutions - 1 - resno - res->pdy));
         else
            dy = opj_pi_min(pi->dy, comp->dy * (1 << (comp->numresolutions - 1 - resno - res->pdy)));
         pi->dy = dy;
      }
   }
   if (pi->tp_on == 0)
   {
      pi->poc.ty0 = pi->ty0;
      pi->poc.tx0 = pi->tx0;
      pi->poc.ty1 = pi->ty1;
      pi->poc.tx1 = pi->tx1;
   }
   for (pi->resno = pi->poc.resno0; pi->resno < pi->poc.resno1; pi->resno++)
   {
      for (pi->y = pi->poc.ty0; pi->y < pi->poc.ty1; pi->y += (pi->dy - (pi->y % pi->dy)))
      {
         for (pi->x = pi->poc.tx0; pi->x < pi->poc.tx1; pi->x += (pi->dx - (pi->x % pi->dx)))
         {
            for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++)
            {
               comp = &pi->comps[pi->compno];
               if (pi->resno < comp->numresolutions)
               {
                  res = &comp->resolutions[pi->resno];
                  levelno = comp->numresolutions - 1 - pi->resno;
                  trx0 = opj_pi_div(pi->tx0, (comp->dx << levelno));
                  try0 = opj_pi_div(pi->ty0, (comp->dy << levelno));
                  trx1 = opj_pi_div(pi->tx1, (comp->dx << levelno));
                  try1 = opj_pi_div(pi->ty1, (comp->dy << levelno));
                  rpx = res->pdx + levelno;
                  rpy = res->pdy + levelno;
                  if ((pi->y % (comp->dy << rpy)) == 0 || (pi->y == pi->ty0 && (opj_pi_div(pi->y, (comp->dy << rpy)) % 1 == 0)))
                  {
                     if ((pi->x % (comp->dx << rpx)) == 0 || (pi->x == pi->tx0 && (opj_pi_div(pi->x, (comp->dx << rpx)) % 1 == 0)))
                     {
                        if (res->pw != 0 && res->ph != 0 && trx0 != trx1 && try0 != try1)
                        {
                           prci = opj_pi_div(opj_pi_div(pi->x, (comp->dx << levelno)), res->pdx);
                           prci = prci - opj_pi_div(trx0, res->pdx);
                           prcy = opj_pi_div(opj_pi_div(pi->y, (comp->dy << levelno)), res->pdy);
                           prcy = prcy - opj_pi_div(try0, res->pdy);
                           pi->precno = (prci + (res->pw * prcy));
                           for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++)
                           {
                              index = (pi->step_p * pi->precno +
                                       pi->step_c * pi->compno +
                                       pi->step_r * pi->resno +
                                       pi->step_l * pi->layno);
                              if (pi->include[index] == 0)
                              {
                                 pi->include[index] = 1;
                                 return 1;
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   return 0;
}