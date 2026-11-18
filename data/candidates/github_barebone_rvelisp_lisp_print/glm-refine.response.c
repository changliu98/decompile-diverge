void __cdecl print(double x)
{
    switch (T(x))
    {
        case TAG_PRIMITIVE:
            fprintf(out, "<%s>", prim[ord(x)]);
            break;
        case TAG_SYMBOL:
            fprintf(out, "%s", (const char *)cell + ord(x));
            break;
        case TAG_STRING:
            fprintf(out, "\"%s\"", (const char *)cell + ord(x));
            break;
        case TAG_LIST:
            printlist(x);
            break;
        case TAG_OBJECT:
            fprintf(out, "{%u}", ord(x));
            break;
        case TAG_ARRAY:
            fprintf(out, "[%u]", ord(x));
            break;
        case TAG_NIL:
            fprintf(out, "()");
            break;
        default:
            // Fallback for standard floating point numbers
            fprintf(out, "%.17lg", x);
            break;
    }
}