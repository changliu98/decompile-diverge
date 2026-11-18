uint32_t hsv2grb(uint16_t h, uint8_t s, uint8_t v) {
    uint16_t region = h / 360;
    uint16_t rem = h % 360;
    uint16_t region6 = rem / 60;
    
    uint16_t v_val = v;
    uint16_t inv = (s ^ 0xFF);
    uint16_t min_val = (inv * v) >> 8;
    uint16_t diff = v_val - min_val;
    
    uint16_t h_mod = rem % 60;
    uint16_t h_inv = 60 - h_mod;
    
    uint8_t r, g, b;
    
    switch (region6) {
        case 0:
            r = v_val;
            g = min_val + (diff * h_mod) / 32;
            b = min_val;
            break;
        case 1:
            r = min_val + (diff * h_inv) / 32;
            g = v_val;
            b = min_val;
            break;
        case 2:
            r = min_val;
            g = v_val;
            b = min_val + (diff * h_mod) / 32;
            break;
        case 3:
            r = min_val;
            g = min_val + (diff * h_inv) / 32;
            b = v_val;
            break;
        case 4:
            r = min_val + (diff * h_mod) / 32;
            g = min_val;
            b = v_val;
            break;
        case 5:
            r = v_val;
            g = min_val;
            b = min_val + (diff * h_inv) / 32;
            break;
        default:
            r = 0;
            g = 0;
            b = 0;
            break;
    }
    
    return ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
}