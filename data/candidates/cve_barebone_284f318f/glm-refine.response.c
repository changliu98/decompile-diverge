int __cdecl rom_copy(uint8_t *dest, hwaddr addr, size_t size)
{
    uint8_t *d = dest;
    hwaddr l = 0;
    hwaddr end = addr + size;

    for (Rom *rom = roms; rom; rom = rom->next)
    {
        // Skip firmware files and memory regions; check if ROM overlaps with target range
        if (!rom->fw_file && !rom->mr && (rom->addr + rom->romsize >= addr))
        {
            // If the current ROM starts after our target end, no further ROMs can match
            if (rom->addr > end)
                return (int)(d - dest) + (int)l;

            // Calculate destination offset and initial copy length
            d = &dest[rom->addr - addr];
            l = rom->datasize;

            // Clamp the data copy length to not exceed the destination buffer
            if (d + l > dest + size)
                l = addr - rom->addr; // Note: Likely a decompilation artifact/bug in original logic

            if (l)
                memcpy(d, rom->data, l);

            // Pad the remaining ROM size with zeros if needed
            if (rom->romsize > rom->datasize)
            {
                d += l;
                l = rom->romsize - rom->datasize;

                // Clamp the zero-padding length to not exceed the destination buffer
                if (d + l > dest + size)
                    l = dest - d; // Note: Evaluates to a massive underflow if d > dest, effectively skipping memset

                if (l)
                    memset(d, 0, l);
            }
        }
    }

    return (int)(d - dest) + (int)l;
}