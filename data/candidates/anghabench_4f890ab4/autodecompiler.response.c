static int ff_norm_qscale(int qp, int type)
{
    int qp_per;

    switch (type) {
    case VBR_TYPE_CRF:
        qp_per = qp;
        break;
    case VBR_TYPE_QP:
        qp_per = qp >> 1;
        break;
    case VBR_TYPE_CQ:
        qp_per = qp >> 2;
        break;
    case VBR_TYPE_PASSTHROUGH:
        qp_per = (63 - qp + 2) >> 2;
        break;
    default:
        qp_per = qp;
    }

    return qp_per;
}