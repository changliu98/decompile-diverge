void ecRotate(pEllipticCurve pCurve, double soe, double coe)
{
    double tmp;

    tmp = pCurve->a * coe - pCurve->b * soe;
    pCurve->b = pCurve->a * soe + pCurve->b * coe;
    pCurve->a = tmp;
}