void fmtutil_macbitmap_read_pixmap_only_fields(de_ctx *ctx, dbuf *f, macbitmap *mb, int64_t pos) {
    uint16_t v0;
    uint32_t v1, v2, v3;
    
    de_dbg(ctx, "pixmap only fields, pos=%d", (int)pos);
    de_dbg_indent(ctx, 1);
    
    v0 = dbuf_getu16be(f, pos + 0);
    de_dbg(ctx, "version: %d", (int)v0);
    
    mb->field_30 = dbuf_getu16be(f, pos + 2);
    de_dbg(ctx, "packType: %d", (int)mb->field_30);
    
    v1 = dbuf_getu32be(f, pos + 4);
    de_dbg(ctx, "packSize: %d", (int)v1);
    
    mb->field_58 = pict_read_fixed(f, pos + 8);
    mb->field_60 = pict_read_fixed(f, pos + 12);
    de_dbg(ctx, "hRes, vRes: %f, %f", mb->field_58, mb->field_60);
    
    mb->field_38 = dbuf_getu16be(f, pos + 16);
    mb->field_40 = dbuf_getu16be(f, pos + 18);
    mb->field_48 = dbuf_getu16be(f, pos + 20);
    mb->field_50 = dbuf_getu16be(f, pos + 22);
    de_dbg(ctx, "pixelType, pixelSize, cmpCount, cmpSize: %d, %d, %d, %d", 
            (int)mb->field_38, (int)mb->field_40, (int)mb->field_48, (int)mb->field_50);
            
    mb->field_18 = (mb->field_0 * 8) / mb->field_40;
    if (mb->field_18 < mb->field_10) {
        mb->field_18 = mb->field_10;
    }
    
    v2 = dbuf_getu32be(f, pos + 24);
    de_dbg(ctx, "planeByte: %d", (int)v2);
    
    mb->field_68 = dbuf_getu32be(f, pos + 28);
    de_dbg(ctx, "pmTable: %d", (int)mb->field_68);
    
    v3 = dbuf_getu32be(f, pos + 32);
    de_dbg(ctx, "pmExt: %d", (int)v3);
    
    de_dbg_indent(ctx, -1);
}