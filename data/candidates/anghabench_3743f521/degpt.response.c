/*
 * SSL_alert_desc_string_long - Convert an SSL alert description value to its long-form string representation.
 *
 * @value: The raw alert value (typically from an SSL alert record).
 *
 * This function masks the input value to the lower 8 bits (0x00-0xFF) to extract
 * the alert description code, as defined in the TLS/SSL protocol specification.
 * It then maps this code to a human-readable string.
 *
 * Returns: A static string describing the alert, or "unknown" if the code is not recognized.
 */
char * SSL_alert_desc_string_long(int alert_code)
{
    /* Mask to get the alert description byte (lower 8 bits) */
    switch(alert_code & 0xff) {
    case 0x80: return "user canceled";
    case 0x81: return "unsupported extension";
    case 0x82: return "unrecognized name";
    case 0x83: return "unknown PSK identity";
    case 0x84: return "unknown CA";
    case 0x85: return "record overflow";
    case 0x86: return "protocol version";
    case 0x87: return "no renegotiation";
    case 0x88: return "no application protocol";
    case 0x89: return "internal error";
    case 0x8a: return "insufficient security";
    case 0x8b: return "export restriction";
    case 0x8c: return "decrypt error";
    case 0x8d: return "decryption failed";
    case 0x8e: return "decode error";
    case 0x8f: return "certificate unobtainable";
    case 0x90: return "bad certificate status response";
    case 0x91: return "bad certificate hash value";
    case 0x92: return "access denied";
    case 0x93: return "unsupported certificate";
    case 0x94: return "unexpected_message";
    case 0x95: return "no certificate";
    case 0x96: return "illegal parameter";
    case 0x97: return "handshake failure";
    case 0x98: return "decompression failure";
    case 0x99: return "close notify";
    case 0x9a: return "certificate unknown";
    case 0x9b: return "certificate revoked";
    case 0x9c: return "certificate expired";
    case 0x9d: return "bad record mac";
    case 0x9e: return "bad certificate";
    default: return "unknown";
    }
}