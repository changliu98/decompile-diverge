define CAC_CERT_TYPE_COMPRESSED         0x01

int __cdecl cac_read_binary(
        sc_card_t *card,
        unsigned int idx,
        unsigned __int8 *buf,
        size_t count,
        unsigned __int64 flags)
{
    cac_private_data_t *priv = (cac_private_data_t *)card->drv_data;
    u8 *val = NULL;
    size_t val_len = 0;
    int r;

    // 1. Serve from cache if already cached
    if (priv->cached) 
    {
        if (idx > priv->cache_buf_len)
            return SC_ERROR_FILE_END_REACHED;
        
        size_t to_read = count;
        if (to_read >= priv->cache_buf_len - idx)
            to_read = priv->cache_buf_len - idx;
            
        memcpy(buf, &priv->cache_buf[idx], to_read);
        return to_read;
    }

    // 2. Clear any stale cache data
    free(priv->cache_buf);
    priv->cache_buf = NULL;
    priv->cache_buf_len = 0;

    // 3. Fetch the certificate blob from the card
    r = cac_cac1_get_certificate(card, &val, &val_len);
    if (r >= 0) 
    {
        if (val_len == 0) 
        {
            r = SC_ERROR_FILE_NOT_FOUND;
        } 
        else 
        {
            u8 cert_type = val[0];
            u8 *cert_ptr = val + 1;
            size_t cert_len = val_len - 1;

            // Check if the certificate is compressed (bit 0 set)
            if ((cert_type & 0x03) == CAC_CERT_TYPE_COMPRESSED) 
            {
                r = SC_ERROR_INVALID_DATA;
            } 
            else if (val_len != 1) 
            {
                // Allocate and populate the cache with uncompressed cert data
                priv->cache_buf = (u8 *)malloc(cert_len);
                if (!priv->cache_buf) 
                {
                    r = SC_ERROR_OUT_OF_MEMORY;
                    goto done;
                }
                priv->cache_buf_len = cert_len;
                memcpy(priv->cache_buf, cert_ptr, cert_len);
                
                // Fallthrough to cache read logic below
            }

            // 4. Serve the requested data from the newly populated cache
            if (r >= 0) 
            {
                priv->cached = 1;
                
                size_t to_read = count;
                if (to_read >= priv->cache_buf_len - idx)
                    to_read = priv->cache_buf_len - idx;
                    
                if (to_read && priv->cache_buf)
                    memcpy(buf, &priv->cache_buf[idx], to_read);
                    
                r = to_read;
            }
        }
    }

done:
    if (val)
        free(val);
        
    return r;
}