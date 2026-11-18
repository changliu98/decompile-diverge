int xrdp_wm_parse_domain_information(char *domain, int combo_max, int decode, char *result)
{
    int pos;
    int ret = 0;

    memset(result, 0, 256);

    switch(domain[0])
    {
        case '_':
            pos = g_pos(domain + 1, "__");
            if(pos > 0)
            {
                if(decode)
                {
                    char num[2];
                    int i;

                    memset(num, 0, 2);
                    g_strncpy(num, domain + pos + 3, 1);
                    i = g_htoi(num);
                    if(i > 0 && i < combo_max)
                        ret = i;
                }
                else
                {
                    g_strncpy(result, domain + 1, pos);
                }
            }
            else
            {
                g_strncpy(result, domain + 1, 255);
            }
            break;
        default:
            return ret;
    }

    return ret;
}