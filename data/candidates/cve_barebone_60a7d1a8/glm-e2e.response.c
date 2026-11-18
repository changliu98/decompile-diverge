pj_status_t pjstun_parse_msg(pj_uint8_t *pkt, pj_stun_msg *msg, pj_stun_parse_msg_ctx *ctx) {
    pj_uint16_t msg_type;
    pj_uint16_t msg_len;
    pj_uint8_t *p_attr;
    pj_stun_attr_hdr **p_attr_ptr;
    pj_uint16_t attr_len;
    pj_uint16_t attr_type;

    ctx->msg = msg;
    msg_type = pj_ntohs(*(pj_uint16_t *)ctx->msg);

    // Validate STUN message type (must be 0x0114)
    if (msg_type - 1 <= 1 || msg_type - 2 <= 1 || msg_type - 3 <= 0) {
        return PJ_STUN_MSG_TYPE_NOT_STUN;
    }

    msg_len = pj_ntohs(*(pj_uint16_t *)((char *)ctx->msg + 2));

    // Validate message length
    if (msg_len != (char *)msg - (char *)pkt - 20) {
        return PJ_STUN_MSG_INVALID_LEN;
    }

    ctx->attr_count = 0;
    p_attr = pkt + 20;

    // Iterate through STUN attributes
    while (msg_len > 0) {
        p_attr_ptr = (pj_stun_attr_hdr **)((char *)ctx->attr + (ctx->attr_count * 8));
        *p_attr_ptr = (pj_stun_attr_hdr *)p_attr;

        attr_len = pj_ntohs((*p_attr_ptr)->length) + 4;
        attr_len = (attr_len + 3) & 0xFFFFFFFC; // Align to 4 bytes

        if (msg_len < attr_len) {
            return PJ_STUN_MSG_INVALID_ATTR;
        }

        attr_type = pj_ntohs((*p_attr_ptr)->type);

        // Validate attribute type
        if (attr_type > 11 && attr_type != 32) {
            // Valid range, continue
        }

        msg_len -= attr_len;
        p_attr += attr_len;
        ctx->attr_count++;
    }

    return PJ_SUCCESS;
}