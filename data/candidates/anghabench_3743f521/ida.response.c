const char *__cdecl SSL_alert_desc_string_long(int value)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( (char)value )
  {
    case -128:
      v2 = "user canceled";
      break;
    case -127:
      v2 = "unsupported extension";
      break;
    case -126:
      v2 = "unrecognized name";
      break;
    case -125:
      v2 = "unknown PSK identity";
      break;
    case -124:
      v2 = "unknown CA";
      break;
    case -123:
      v2 = "record overflow";
      break;
    case -122:
      v2 = "protocol version";
      break;
    case -121:
      v2 = "no renegotiation";
      break;
    case -120:
      v2 = "no application protocol";
      break;
    case -119:
      v2 = "internal error";
      break;
    case -118:
      v2 = "insufficient security";
      break;
    case -117:
      v2 = "export restriction";
      break;
    case -116:
      v2 = "decrypt error";
      break;
    case -115:
      v2 = "decryption failed";
      break;
    case -114:
      v2 = "decode error";
      break;
    case -113:
      v2 = "certificate unobtainable";
      break;
    case -112:
      v2 = "bad certificate status response";
      break;
    case -111:
      v2 = "bad certificate hash value";
      break;
    case -110:
      v2 = "access denied";
      break;
    case -109:
      v2 = "unsupported certificate";
      break;
    case -108:
      v2 = "unexpected_message";
      break;
    case -107:
      v2 = "no certificate";
      break;
    case -106:
      v2 = "illegal parameter";
      break;
    case -105:
      v2 = "handshake failure";
      break;
    case -104:
      v2 = "decompression failure";
      break;
    case -103:
      v2 = "close notify";
      break;
    case -102:
      v2 = "certificate unknown";
      break;
    case -101:
      v2 = "certificate revoked";
      break;
    case -100:
      v2 = "certificate expired";
      break;
    case -99:
      v2 = "bad record mac";
      break;
    case -98:
      v2 = "bad certificate";
      break;
    default:
      v2 = "unknown";
      break;
  }
  return v2;
}