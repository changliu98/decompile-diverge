int vis5d_color_table_set_alpha(ColorTable *ct, float alpha) {
    ct->field_0xc = alpha;
    
    if (alpha < 0.0f) {
        ct->field_0x14 = 0.0f;
        ct->field_0x18 = 1.0f;
        
        if (alpha == -1.0f) {
            ct->field_0x8 = 0.0f;
            ct->field_0xc = 1.0f;
        } else {
            ct->field_0x8 = 0.5f;
        }
    } else {
        ct->field_0x14 = alpha;
        ct->field_0x18 = alpha;
        ct->field_0xc = alpha;
    }
    
    return 0;
}