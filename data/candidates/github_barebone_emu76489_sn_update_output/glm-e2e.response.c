void update_output(struct Context *ctx) {
    int32_t v1 = (ctx->field_0x68 + ctx->field_0x0c) & 0xFFFFFFFF;
    ctx->field_0x68 = v1;
    
    int32_t v2 = (uint32_t)v1 >> 24;
    ctx->field_0x68 = v1 & 0xFFFFFF;
    ctx->field_0x54 += v2;
    
    if ((ctx->field_0x54 & 0x100) != 0) {
        if (ctx->field_0x60 != 0) {
            int32_t v3 = (uint32_t)ctx->field_0x50 >> 1;
            int32_t v4 = parity(ctx->field_0x50 & 0x9);
            ctx->field_0x50 = v3 | (v4 << 15);
        } else {
            int32_t v5 = (uint32_t)ctx->field_0x50 >> 1;
            ctx->field_0x50 = v5 | ((ctx->field_0x50 & 1) << 15);
        }
        
        if (ctx->field_0x64 != 0) {
            ctx->field_0x54 -= ctx->field_0x34[0];
        } else {
            ctx->field_0x54 -= ctx->field_0x58;
        }
    }
    
    if ((ctx->field_0x50 & 1) != 0) {
        int32_t idx = ctx->field_0x5c;
        int32_t val = table1[idx] << 4;
        ctx->field_0x86 = (int16_t)(val + ctx->field_0x86);
    }
    
    ctx->field_0x86 = (int16_t)(ctx->field_0x86 >> 1);
    
    for (int i = 0; i < 4; i++) {
        ctx->arr_0x14[i] += v2;
        
        if ((ctx->arr_0x14[i] & 0x400) != 0) {
            if (ctx->arr_0x2c[i] > 1) {
                ctx->arr_0x38[i] = !(ctx->arr_0x38[i] != 0) ? 1 : 0;
                ctx->arr_0x14[i] -= ctx->arr_0x2c[i];
            } else {
                ctx->arr_0x38[i] = 1;
            }
        }
        
        if (ctx->arr_0x38[i] != 0 && ctx->arr_0x44[i] == 0) {
            int32_t idx2 = ctx->arr_0x20[i];
            int32_t val2 = table2[idx2] << 4;
            ctx->arr_0x80[i] = (int16_t)(val2 + ctx->arr_0x80[i]);
        }
        
        ctx->arr_0x80[i] = (int16_t)(ctx->arr_0x80[i] >> 1);
    }
}