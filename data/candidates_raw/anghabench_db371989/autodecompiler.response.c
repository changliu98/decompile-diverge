char *getStatusCodeName(int code)
{
    char *name;

    switch (code) {
        case 206:
            name = "Partial Content";
            break;
        case 301:
            name = "Moved";
            break;
        case 302:
            name = "Found";
            break;
        case 400:
            name = "Bad Request";
            break;
        case 401:
            name = "Unauthorized";
            break;
        case 403:
            name = "Forbidden";
            break;
        case 404:
            name = "Not Found";
            break;
        case 416:
            name = "Requested Range Not Satisfiable";
            break;
        case 418:
            name = "I'm a teapot";
            break;
        case 500:
            name = "Internal Server Error";
            break;
        case 502:
            name = "Bad Gateway";
            break;
        case 503:
            name = "Service Unavailable";
            break;
        default:
            name = "OK";
    }

    return name;
}