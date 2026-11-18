const char *SSL_alert_desc_string_long(int value) {
  const char *s;
  switch (value & 0xff) {
    case SSL3_AD_CLOSE_NOTIFY:
      s = "close notify";
      break;
    case SSL3_AD_UNEXPECTED_MESSAGE:
      s = "unexpected_message";
      break;
    case SSL3_AD_BAD_RECORD_MAC:
      s = "bad record mac";
      break;
    case SSL3_AD_DECOMPRESSION_FAILURE:
      s = "decompression failure";
      break;
    case SSL3_AD_HANDSHAKE_FAILURE:
      s = "handshake failure";
      break;
    case SSL3_AD_NO_CERTIFICATE:
      s = "no certificate";
      break;
    case SSL3_AD_BAD_CERTIFICATE:
      s = "bad certificate";
      break;
    case SSL3_AD_UNSUPPORTED_CERTIFICATE:
      s = "unsupported certificate";
      break;
    case SSL3_AD_CERTIFICATE_REVOKED:
      s = "certificate revoked";
      break;
    case SSL3_AD_CERTIFICATE_EXPIRED:
      s = "certificate expired";
      break;
    case SSL3_AD_CERTIFICATE_UNKNOWN:
      s = "certificate unknown";
      break;
    case SSL3_AD_ILLEGAL_PARAMETER:
      s = "illegal parameter";
      break;
    case TLS1_AD_DECRYPTION_FAILED:
      s = "decryption failed";
      break;
    case TLS1_AD_RECORD_OVERFLOW:
      s = "record overflow";
      break;
    case TLS1_AD_UNKNOWN_CA:
      s = "unknown CA";
      break;
    case TLS1_AD_ACCESS_DENIED:
      s = "access denied";
      break;
    case TLS1_AD_DECODE_ERROR:
      s = "decode error";
      break;
    case TLS1_AD_DECRYPT_ERROR:
      s = "decrypt error";
      break;
    case TLS1_AD_EXPORT_RESTRICTION:
      s = "export restriction";
      break;
    case TLS1_AD_PROTOCOL_VERSION:
      s = "protocol version";
      break;
    case TLS1_AD_INSUFFICIENT_SECURITY:
      s = "insufficient security";
      break;
    case TLS1_AD_INTERNAL_ERROR:
      s = "internal error";
      break;
    case TLS1_AD_USER_CANCELLED:
      s = "user canceled";
      break;
    case TLS1_AD_NO_RENEGOTIATION:
      s = "no renegotiation";
      break;
    case TLS1_AD_UNSUPPORTED_EXTENSION:
      s = "unsupported extension";
      break;
    case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
      s = "certificate unobtainable";
      break;
    case TLS1_AD_UNRECOGNIZED_NAME:
      s = "unrecognized name";
      break;
    case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
      s = "bad certificate status response";
      break;
    case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
      s = "bad certificate hash value";
      break;
    case TLS1_AD_UNKNOWN_PSK_IDENTITY:
      s = "unknown PSK identity";
      break;
    case TLS1_AD_NO_APPLICATION_PROTOCOL:
      s = "no application protocol";
      break;
    default:
      s = "unknown";
      break;
  }
  return s;
}