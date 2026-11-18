char * mg_status_message(int http_status)
{
    // Return "Partial Content" for HTTP status code 206 (0xce)
    if (http_status == 0xce) return "Partial Content";
    // Return "Moved" for HTTP status code 301 (0x12d)
    if (http_status == 0x12d) return "Moved";
    // Return "Found" for HTTP status code 302 (0x12e)
    if (http_status == 0x12e) return "Found";
    // Return "Bad Request" for HTTP status code 400
    if (http_status == 400) return "Bad Request";
    // Return "Unauthorized" for HTTP status code 401 (0x191)
    if (http_status == 0x191) return "Unauthorized";
    // Return "Forbidden" for HTTP status code 403 (0x193)
    if (http_status == 0x193) return "Forbidden";
    // Return "Not Found" for HTTP status code 404 (0x194)
    if (http_status == 0x194) return "Not Found";
    // Return "Requested Range Not Satisfiable" for HTTP status code 416 (0x1a0)
    if (http_status == 0x1a0) return "Requested Range Not Satisfiable";
    // Return "I'm a teapot" for HTTP status code 418 (0x1a2)
    if (http_status == 0x1a2) return "I\'m a teapot";
    // Return "Internal Server Error" for HTTP status code 500
    if (http_status == 500) return "Internal Server Error";
    // Return "Bad Gateway" for HTTP status code 502 (0x1f6)
    if (http_status == 0x1f6) return "Bad Gateway";
    // Return "Service Unavailable" for HTTP status code 503 (0x1f7)
    if (http_status == 0x1f7) return "Service Unavailable";
    // Default return value for any other status code
    return "OK";
}