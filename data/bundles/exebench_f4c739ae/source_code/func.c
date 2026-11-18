














double randum (long *seed)

  {
    long sum, mult0, mult1, seed0, seed1, seed2, newseed0, newseed1, newseed2;
    double res;

    mult0 = 1549;
    seed0 = *seed & 4095;
    sum = mult0 * seed0;
    newseed0 = sum & 4095;
    sum >>= 12;
    seed1 = (*seed >> 12) & 4095;
    mult1 = 406;
    sum += mult0 * seed1 + mult1 * seed0;
    newseed1 = sum & 4095;
    sum >>= 12;
    seed2 = (*seed >> 24) & 255;
    sum += mult0 * seed2 + mult1 * seed1;
    newseed2 = sum & 255;

    *seed = newseed2 << 24 | newseed1 << 12 | newseed0;
    res = 0.00390625 * (newseed2 + 0.000244140625 * (newseed1 + 0.000244140625 * newseed0));

    return res;
  }
