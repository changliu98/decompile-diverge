int __cdecl ff_norm_qscale(int qscale, int type)
{
    switch (type)
    {
        case 128:
            return (65 - qscale) >> 2;
        case 129:
            return qscale >> 1;
        case 131:
            return qscale >> 2;
        case 130:
        default:
            return qscale;
    }
}