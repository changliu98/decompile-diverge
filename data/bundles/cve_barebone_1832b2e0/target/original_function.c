static int
xrdp_wm_parse_domain_information(char *originalDomainInfo, int comboMax,
                                 int decode, char *resultBuffer)
{
    int ret;
    int pos;
    int comboxindex;
    char index[2];

    /* If the first char in the domain name is '_' we use the domain
       name as IP*/
    ret = 0; /* default return value */
    /* resultBuffer assumed to be 256 chars */
    g_memset(resultBuffer, 0, 256);
    if (originalDomainInfo[0] == '_')
    {
        /* we try to locate a number indicating what combobox index the user
         * prefer the information is loaded from domain field, from the client
         * We must use valid chars in the domain name.
         * Underscore is a valid name in the domain.
         * Invalid chars are ignored in microsoft client therefore we use '_'
         * again. this sec '__' contains the split for index.*/
        pos = g_pos(&originalDomainInfo[1], "__");
        if (pos > 0)
        {
            /* an index is found we try to use it */
            LOG(LOG_LEVEL_DEBUG, "domain contains index char __");
            if (decode)
            {
                g_memset(index, 0, 2);
                /* we just accept values 0-9  (one figure) */
                g_strncpy(index, &originalDomainInfo[pos + 3], 1);
                comboxindex = g_htoi(index);
                LOG(LOG_LEVEL_DEBUG,
                    "index value as string: %s, as int: %d, max: %d",
                    index, comboxindex, comboMax - 1);
                /* limit to max number of items in combo box */
                if ((comboxindex > 0) && (comboxindex < comboMax))
                {
                    LOG(LOG_LEVEL_DEBUG, "domain contains a valid "
                        "index number");
                    ret = comboxindex; /* preferred index for combo box. */
                }
            }
            /* pos limit the String to only contain the IP */
            g_strncpy(resultBuffer, &originalDomainInfo[1], pos);
        }
        else
        {
            LOG(LOG_LEVEL_DEBUG, "domain does not contain _");
            g_strncpy(resultBuffer, &originalDomainInfo[1], 255);
        }
    }
    return ret;
}