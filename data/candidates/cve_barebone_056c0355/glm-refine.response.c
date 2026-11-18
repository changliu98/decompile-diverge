void __cdecl xmlrpc_char_encode(char *outbuffer, const char *input_str)
{
    char entity_buf[15];
    mowgli_string_t *str_obj;
    unsigned __int8 c;
    unsigned __int64 i;

    // Initialize buffers
    entity_buf[0] = 0;
    *outbuffer = 0;

    str_obj = mowgli_string_create();

    if (input_str && *input_str)
    {
        for (i = 0; input_str[i]; ++i)
        {
            c = (unsigned __int8)input_str[i];

            if (c <= 0x7F)
            {
                // Encode standard XML entities
                switch (c)
                {
                    case '&':
                        str_obj->append(str_obj, "&amp;", 5);
                        break;
                    case '<':
                        str_obj->append(str_obj, "&lt;", 4);
                        break;
                    case '>':
                        str_obj->append(str_obj, "&gt;", 4);
                        break;
                    case '"':
                        str_obj->append(str_obj, "&quot;", 6);
                        break;
                    default:
                        str_obj->append_char(str_obj, c);
                        break;
                }
            }
            else
            {
                // Encode non-ASCII bytes as numeric XML entities
                snprintf(entity_buf, 0xF, "&#%d;", c);
                str_obj->append(str_obj, entity_buf, strlen(entity_buf));
            }
        }
        
        // Copy the constructed string to the output buffer (fixed 4096 byte copy)
        memcpy(outbuffer, str_obj->str, 0x1000);
    }
}