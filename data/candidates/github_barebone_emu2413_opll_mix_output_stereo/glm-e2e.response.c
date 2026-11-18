void mix_output_stereo(struct OPLL *ctx) {
    // ctx + 0xe28 is a pointer to a struct containing two int16_t values
    struct {
        int16_t left;
        int16_t right;
    } *out = (void *)((char *)ctx + 0xe28);
    
    out->left = 0;
    out->right = 0;
    
    for (int i = 0; i < 14; i++) {
        // ctx + 0xd78 is an array of uint8_t
        uint8_t mask = *((uint8_t *)ctx + 0xd78 + i);
        
        // Left channel
        if (mask & 0x2) {
            // ctx + 0xe0c is an array of int16_t
            int16_t sample = *((int16_t *)ctx + 0xe0c + i);
            // ctx + 0xd88 is an array of float (left channel volume)
            float vol = *((float *)ctx + 0xd88 + i);
            int16_t mixed = (int16_t)(sample * vol);
            out->left += mixed;
        }
        
        // Right channel
        if (mask & 0x1) {
            // ctx + 0xe0c is an array of int16_t
            int16_t sample = *((int16_t *)ctx + 0xe0c + i);
            // ctx + 0xd8c is an array of float (right channel volume)
            float vol = *((float *)ctx + 0xd8c + i);
            int16_t mixed = (int16_t)(sample * vol);
            out->right += mixed;
        }
    }
    
    // ctx + 0xe30 is a function pointer
    void (*callback)(struct OPLL *, int, int) = *(void (**)(struct OPLL *, int, int))((char *)ctx + 0xe30);
    if (callback) {
        callback(ctx, 0, out->left);
        callback(ctx, 1, out->right);
    }
}