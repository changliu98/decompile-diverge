void *rom_copy(void *dst, uint64_t addr, uint64_t size) {
    void *end = (char *)dst + size;
    void *ptr = dst;
    uint64_t remaining = 0;
    
    for (struct rom *rom = roms; rom != NULL; rom = rom->next) {
        if (rom->is_loaded != 0) continue;
        if (rom->field_28 != NULL) continue;
        
        if (rom->rom_addr + rom->rom_size < addr) continue;
        if (rom->rom_addr > end) break;
        
        ptr = (char *)dst + (rom->rom_addr - addr);
        const void *src = rom->rom_data;
        remaining = rom->copy_size;
        
        if ((char *)ptr + remaining > (char *)dst + size) {
            remaining = (char *)dst + size - (char *)ptr;
        }
        
        if (remaining > 0) {
            memcpy(ptr, src, remaining);
        }
        
        if (rom->rom_size > rom->copy_size) {
            ptr = (char *)ptr + remaining;
            remaining = rom->rom_size - rom->copy_size;
            
            if ((char *)ptr + remaining > (char *)dst + size) {
                remaining = (char *)dst + size - (char *)ptr;
            }
            
            if (remaining > 0) {
                memset(ptr, 0, remaining);
            }
        }
    }
    
    return (char *)ptr + remaining - (char *)dst;
}