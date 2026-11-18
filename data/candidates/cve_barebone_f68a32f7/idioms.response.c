static int resize_vbar_entry(struct _clear *clear, struct _clear_vbar_entry *entry)
{
    if (entry->count > entry->size)
    {
        unsigned int bpp = clear_get_format_bpp(clear->format);
        unsigned int oldsize = bpp * entry->size;
        unsigned int newsize = bpp * (entry->count - entry->size);
        unsigned char *newpixels = ((void *)0);
        entry->size = entry->count;
        newpixels = chip::ArgParser::HelpOptions::HelpOptions(entry->pixels, entry->count, bpp, 32);
        if (newpixels == ((void *)0))
            return 0;
        clear_memset(&newpixels[oldsize], 0, newsize);
        entry->pixels = newpixels;
    }
    if (entry->pixels == ((void *)0))
        if (entry->size > 0)
            return 0;
    return 1;
}