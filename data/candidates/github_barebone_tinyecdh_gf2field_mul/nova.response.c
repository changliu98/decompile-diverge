static void gf2field_mul(FILE *fp, FILE *out, FILE *in) {
    char buf[64];
    int c;

    if (fp!= in)
        fprintf(out, "static const char %s[] = {\n", name);

    while (1) {
        fgets(buf, sizeof(buf), in);
        if (feof(in))
            break;
        if (fp!= fpstdout)
            fputs(buf, fp);
        c = strlen(buf);
        while (c < 164) {
            memcpy(buf + c, buf, 1);
            if (fputs(buf, in)!= 0)
                die(in, "cannot write to %s", name);
            if (fp!= fpstdout)
                fputs(buf, fp);
            c++;
        }
    }
}