int utf8proc_grapheme_break_stateful(int codepoint1, int codepoint2, void *state) {
    utf8proc_property_t *prop1 = utf8proc_get_property(codepoint1);
    utf8proc_property_t *prop2 = utf8proc_get_property(codepoint2);
    
    // Extract bits 24-29 (6 bits) from the 0x12 offset field
    int lbc = (prop1->field_0x12 >> 24) & 0x3F;
    int tbc = (prop2->field_0x12 >> 24) & 0x3F;
    
    // Extract bits 30-31 (2 bits) from the 0x12 offset field
    int prop1_ext = prop1->field_0x12 >> 30;
    int prop2_ext = prop2->field_0x12 >> 30;
    
    // Call the extended grapheme break function
    int result = grapheme_break_extended(lbc, tbc, prop1_ext, prop2_ext, state);
    
    // Return 1 if true, 0 if false (booleanize the result)
    return result & 1;
}