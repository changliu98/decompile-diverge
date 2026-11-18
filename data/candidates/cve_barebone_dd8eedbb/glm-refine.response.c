int __cdecl mwifiex_cmd_append_vsie_tlv(mwifiex_private *priv, u16 vsie_mask, u8 **buffer)
{
    int ret_len = 0;
    int id;

    if (!buffer || !*buffer)
        return 0;

    for (id = 0; id < 8; ++id) 
    {
        if (vsie_mask & priv->vs_ie[id].mask) 
        {
            struct mwifiex_ie_types_vendor_param_set *tlv = 
                (struct mwifiex_ie_types_vendor_param_set *)*buffer;
            
            // Length of the IE payload: ie[1] holds the 802.11 standard IE length.
            // We add 2 to account for the element ID and length byte of the IE itself.
            u16 ie_len = priv->vs_ie[id].ie[1] + 2;
            
            tlv->type = cpu_to_le16(0x010A); // 266 decimal
            tlv->len = cpu_to_le16(ie_len);
            
            // Copy the IE data into the TLV payload
            memcpy(tlv->ie_data, priv->vs_ie[id].ie, ie_len);
            
            // Advance the buffer pointer by the total TLV size (4-byte header + payload)
            *buffer += sizeof(*tlv) + ie_len;
            ret_len += sizeof(*tlv) + ie_len;
        }
    }
    
    return ret_len;
}