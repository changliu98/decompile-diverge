const char *SSL_alert_desc_string_long(int value)
{
    switch (value & 0xff) {
    case SSL3_AL_WARNING:
        return ("W");
    case SSL3_AL_FATAL:
        return ("F");
    default:
        return ("U");
    }
}