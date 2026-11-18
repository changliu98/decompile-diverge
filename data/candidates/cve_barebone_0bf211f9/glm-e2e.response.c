define AV_LOG_ERROR 16

int smacker_decode_tree(Bitstream *bs, SmackerTreeContext *ctx, int value, int depth) {
    int ret;

    if (bitstream_read_bit(bs) == 0) {
        // Leaf node
        if (ctx->current_size >= 256) {
            av_log(NULL, AV_LOG_ERROR, "Error message from 0x2048\n");
            return -1091562057; // 0xbebbb1b7 (likely AVERROR_INVALIDDATA)
        }

        if (depth != 0) {
            ctx->left_child[ctx->current_size] = value;
            ctx->right_child[ctx->current_size] = depth;
        } else {
            ctx->left_child[ctx->current_size] = 0;
            ctx->right_child[ctx->current_size] = 0;
        }

        ctx->values[ctx->current_size] = bitstream_read(bs, 8);
        ctx->current_size++;

        if (ctx->length < depth) {
            ctx->length = depth;
        }

        return 0;
    } else {
        // Internal node
        depth++;
        
        // Recurse for left child
        ret = smacker_decode_tree(bs, ctx, value, depth);
        if (ret != 0) {
            return ret;
        }

        // Recurse for right child, modifying the value with a bit set at the current depth
        int new_value = value | (1 << (depth - 1));
        ret = smacker_decode_tree(bs, ctx, new_value, depth);
        
        return ret;
    }
}