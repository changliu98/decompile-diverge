const char *mg_status_message(int status) {
    const char *msg;

    switch (status) {
        case 0xCE:  // 206
            msg = "OK";
            break;
        case 0x12D: // 301
            msg = "Moved Permanently";
            break;
        case 0x12E: // 302
            msg = "Found";
            break;
        case 0x190: // 400
            msg = "Bad Request";
            break;
        case 0x191: // 401
            msg = "Unauthorized";
            break;
        case 0x193: // 403
            msg = "Forbidden";
            break;
        case 0x194: // 404
            msg = "Not Found";
            break;
        case 0x1A0: // 416
            msg = "Range Not Satisfiable";
            break;
        case 0x1A2: // 418
            msg = "Internal Server Error";
            break;
        case 0x1F4: // 500
            msg = "Internal Server Error";
            break;
        case 0x1F6: // 502
            msg = "Bad Gateway";
            break;
        case 0x1F7: // 503
            msg = "Service Unavailable";
            break;
        default:
            msg = "Unknown";
            break;
    }

    return msg;
}