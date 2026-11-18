const char *SSL_alert_desc_string_long(int value)
{
    switch (value & 0xff) {
    case SSL3_AD_CLOSE_NOTIFY:
        return "close notify";
    case SSL3_AD_UNEXPECTED_MESSAGE:
        return "unexpected_message";
    case SSL3_AD_BAD_RECORD_MAC:
        return "bad record mac";
    case SSL3_AD_DECOMPRESSION_FAILURE:
        return "decompression failure";
    case SSL3_AD_HANDSHAKE_FAILURE:
        return "handshake failure";
    case SSL3_AD_NO_CERTIFICATE:
        return "no certificate";
    case SSL3_AD_BAD_CERTIFICATE:
        return "bad certificate";
    case SSL3_AD_UNSUPPORTED_CERTIFICATE:
        return "unsupported certificate";
    case SSL3_AD_CERTIFICATE_REVOKED:
        return "certificate revoked";
    case SSL3_AD_CERTIFICATE_EXPIRED:
        return "certificate expired";
    case SSL3_AD_CERTIFICATE_UNKNOWN:
        return "certificate unknown";
    case SSL3_AD_ILLEGAL_PARAMETER:
        return "illegal parameter";
    case TLS1_AD_DECRYPTION_FAILED:
        return "decryption failed";
    case TLS1_AD_RECORD_OVERFLOW:
        return "record overflow";
    case TLS1_AD_UNKNOWN_CA:
        return "unknown CA";
    case TLS1_AD_ACCESS_DENIED:
        return "access denied";
    case TLS1_AD_DECODE_ERROR:
        return "decode error";
    case TLS1_AD_DECRYPT_ERROR:
        return "decrypt error";
    case TLS1_AD_EXPORT_RESTRICTION:
        return "export restriction";
    case TLS1_AD_PROTOCOL_VERSION:
        return "protocol version";
    case TLS1_AD_INSUFFICIENT_SECURITY:
        return "insufficient security";
    case TLS1_AD_INTERNAL_ERROR:
        return "internal error";
    case TLS1_AD_USER_CANCELLED:
        return "user canceled";
    case TLS1_AD_NO_RENEGOTIATION:
        return "no renegotiation";
    case TLS1_AD_UNSUPPORTED_EXTENSION:
        return "unsupported extension";
    case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
        return "certificate unobtainable";
    case TLS1_AD_UNRECOGNIZED_NAME:
        return "unrecognized name";
    case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
        return "bad certificate status response";
    case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
        return "bad certificate hash value";
    case TLS1_AD_UNKNOWN_PSK_IDENTITY:
        return "unknown PSK identity";
    case TLS1_AD_NO_APPLICATION_PROTOCOL:
        return "no application protocol";
    default:
        return "unknown";
    }
}