bool __cdecl type_marker_to_cmp_type(uint8_t type_marker, uint8_t *cmp_type)
{
    if (type_marker <= 0x7F)
    {
        *cmp_type = 0;
        return true;
    }
    if (type_marker <= 0x8F)
    {
        *cmp_type = 1;
        return true;
    }
    if (type_marker <= 0x9F)
    {
        *cmp_type = 2;
        return true;
    }
    if (type_marker <= 0xBF)
    {
        *cmp_type = 3;
        return true;
    }
    
    // Range 0xC0 - 0xDF (excluding 0xC1)
    if (type_marker < 0xE0)
    {
        if (type_marker == 0xC1)
            return false;
            
        // Markers 0xC0 and 0xC2..0xDF map linearly to 4..33
        *cmp_type = (type_marker == 0xC0) ? 4 : type_marker + 2;
        return true;
    }
    
    if (type_marker <= 0xFF) // Implied upper bound for uint8_t
    {
        *cmp_type = 34;
        return true;
    }
    
    return false;
}