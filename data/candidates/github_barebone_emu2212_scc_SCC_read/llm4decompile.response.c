uint8_t SCC_read(SCC *scc, uint32_t adr)
{
    uint8_t value;

    if (scc->type == 1 && (adr & 0xFFFE) == 0xBFFE) {
        value = (scc->base_adr >> 8) & 0x20;
    } else if (adr < scc->base_adr) {
        value = 0;
    } else {
        adr -= scc->base_adr;
        if (adr == 0) {
            value = scc->mode ? 0x80 : 0x3F;
        } else if (scc->active && adr >= 0x800 && adr < 0x900) {
            switch (scc->type) {
            case 0:
                value = read_standard(scc, adr);
                break;
            case 1:
                if (scc->mode) {
                    value = read_enhanced(scc, adr);
                } else {
                    value = read_standard(scc, adr);
                }
                break;
            default:
                value = 0;
            }
        } else {
            value = 0;
        }
    }

    return value;
}