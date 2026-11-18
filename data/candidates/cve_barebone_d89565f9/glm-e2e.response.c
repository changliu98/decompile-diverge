void print_attr_string(struct printer_ctx *ctx, const unsigned char *data, int length, unsigned short attr) {
    if (length > 0) {
        if (ctx->length - length > ctx->length || data > ctx->length - length) {
            ctx->print(ctx, "%s", tstr);
            return;
        }
    }

    switch (attr) {
        case 0x3a:
            ctx->print(ctx, " %s", tok2str(rfc4675_tagged, "Unknown", data[0]));
            data++;
            length--;
            break;
        case 0x45:
            if (length < 3) {
                ctx->print(ctx, "%s", tstr);
                return;
            }
            if (data[0] == 0 || data[0] > 0x1f) {
                ctx->print(ctx, "%c", data[0]);
            } else {
                ctx->print(ctx, " ");
            }
            data++;
            length--;
            ctx->print(ctx, "%04x", (data[0] << 8) | data[1]);
            data += 2;
            length -= 2;
            break;
        case 0x41:
        case 0x42:
        case 0x50:
        case 0x51:
        case 0x52:
            if (data[0] <= 0x1f) {
                if (length < 1) {
                    ctx->print(ctx, "%s", tstr);
                    return;
                }
                if (data[0] == 0) {
                    ctx->print(ctx, " ");
                } else {
                    ctx->print(ctx, "%c", data[0]);
                }
                data++;
                length--;
            }
            break;
        default:
            break;
    }

    int i = 0;
    while (data[0] != 0 && i < length) {
        char c = (data[0] >= 0x20 && data[0] <= 0x7e) ? data[0] : '.';
        ctx->print(ctx, "%c", c);
        i++;
        data++;
    }
}