double randlc(long long* xseed)
{
# 123 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/yzhao30/PATO-Pointer-Analysis/refs/heads/master/test/npb2.3-ep/common/c_randdp.c"
    long long sum;
    long long mult0 = 1549;
    long long seed0 = *xseed & 0xfff;
    long long newseed0;
    long long mult1 = 406;
    long long seed1 = (*xseed >> 12) & 0xfff;
    long long newseed1;
    long long seed2 = (*xseed >> 24) & 0xff;
    long long newseed2;
    double ans;

    sum = mult0 * seed0;
    newseed0 = sum & 0xfff;
    sum = (sum >> 12) + mult0 * seed1 + mult1 * seed0;
    newseed1 = sum & 0xfff;
    sum = (sum >> 12) + mult0 * seed2 + mult1 * seed1;
    newseed2 = sum & 0xff;

    *xseed = (newseed2 << 24) | (newseed1 << 12) | newseed0;

    ans = (((double)newseed2 / 256.0 + (double)newseed1) / 256.0 +
           (double)newseed0) / 256.0;

    return ans;
}