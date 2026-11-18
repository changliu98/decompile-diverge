float get_color_value(int varId, struct Tgpd *tgpd, struct Tgpf *tgpf, struct Tgpm *tgpm)
{
    float ret;

    switch (varId & 0x3f) {
    case 9:
        ret = tgpd->Dwel;
        break;
    case 10:
        ret = tgpd->DwelS;
        break;
    case 12:
        ret = tgpd->DwelT;
        break;
    case 17:
        ret = tgpf->Pst;
        break;
    case 18:
        ret = tgpf->PstS;
        break;
    case 20:
        ret = tgpf->PstT;
        break;
    case 33:
        ret = tgpm->Mach;
        break;
    case 34:
        ret = tgpm->MachS;
        break;
    case 36:
        ret = tgpm->MachT;
        break;
    default:
        ret = 0.0f;
    }

    return ret;
}