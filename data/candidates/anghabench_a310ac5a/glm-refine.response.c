bool __cdecl is_special_type(int type)
{
    int lower_nibble = type & 0xF;

    if (lower_nibble == SNDRV_SFNT_PAT_TYPE_GUS)
        return true;
        
    return lower_nibble == SNDRV_SFNT_PAT_TYPE_MAP;
}