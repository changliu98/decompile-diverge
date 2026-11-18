int mwifiex_cmd_append_vsie_tlv(struct mwifiex_private *priv, unsigned short vsie_mask, unsigned char **buf)
{
    int i; int len = 0;
    struct vs_param_set *vs_param_set;
    if (buf == ((void *)0) || *buf == ((void *)0))
        return len;
    for (i = 0; i < 8; i++) {
        if (priv->vs_ie[i].mask & vsie_mask) {
            vs_param_set = (struct vs_param_set *) *buf;
            vs_param_set->type = 0x102;
            vs_param_set->len =
                sizeof(struct vs_param_set) - sizeof(struct vs_param_hdr)
                + priv->vs_ie[i].ie.len;
            memcpy(&vs_param_set->hdr, &priv->vs_ie[i].ie,
                   vs_param_set->len);
            *buf += (vs_param_set->len + sizeof(struct vs_param_hdr));
            len += (vs_param_set->len + sizeof(struct vs_param_hdr));
        }
    }
    return len;
}