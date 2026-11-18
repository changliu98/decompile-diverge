utf8proc_bool __cdecl utf8proc_grapheme_break_stateful(
        utf8proc_int32_t c1,
        utf8proc_int32_t c2,
        utf8proc_int32_t *state)
{
    const utf8proc_property_t *p1 = utf8proc_get_property(c1);
    const utf8proc_property_t *p2 = utf8proc_get_property(c2);

    // Assuming the property struct layout based on the original bit math:
    // Offset 20 (from +18) is a 32-bit integer containing packed properties.
    // Bits 30-31 represent one property (extracted via >> 30)
    // Bits 24-29 represent another property (extracted via HIBYTE & 0x3F)
    
    return grapheme_break_extended(
        (p1->packed_props >> 24) & 0x3F,
        (p2->packed_props >> 24) & 0x3F,
        p1->packed_props >> 30,
        p2->packed_props >> 30,
        state
    );
}