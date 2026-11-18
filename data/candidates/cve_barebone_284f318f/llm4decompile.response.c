int rom_copy(void *dest, hwaddr addr, size_t size)
{
    Rom *rom;
    uint8_t *p, *q;
    size_t s;

    p = dest;
    for(rom = roms.tqh_first; rom != NULL; rom = rom->next.tqe_next) {
        if (rom->fw_file || rom->mr)
            continue;
        if (addr > rom->addr + rom->romsize)
            continue;
        if (addr + size < rom->addr)
            break;
        q = p + (rom->addr - addr);
        s = rom->datasize;
        if (q + s > dest + size)
            s = dest - q;
        if (s > 0)
            memcpy(q, rom->data, s);
        if (rom->datasize < rom->romsize) {
            q += s;
            s = rom->romsize - rom->datasize;
            if (q + s > dest + size)
                s = dest - q;
            if (s > 0)
                memset(q, 0, s);
        }
    }
    return p + s - (uint8_t *)dest;
}