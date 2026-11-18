int vips_source_read_to_memory(struct VipsSource *source)
{
    struct GByteArray *header;
    unsigned char *data;
    long nread;
    do { if (!source->is_pipe) { fprintf (stderr, "assertion failed: %s\n", "!source->is_pipe"); vpix_die (); } } while (0);
    do { if (!source->blob) { fprintf (stderr, "assertion failed: %s\n", "!source->blob"); vpix_die (); } } while (0);
    do { if (!source->header_bytes) { fprintf (stderr, "assertion failed: %s\n", "!source->header_bytes"); vpix_die (); } } while (0);
    do { if (source->length >= 0) { } else { fprintf (stderr, "assertion failed: %s\n", "source->length >= 0"); vpix_die (); } } while (0);
    if (vpix_read_header (source))
        return (-1);
    header = vpix_new_header ();
    vpix_set_header_length (header, source->length);
    for (nread = 0, data = header->data; nread < source->length;) {
        if (source->length - nread < 4096)
            nread += vpix_read_bytes (source, data, 4096);
        else
            nread += vpix_read_bytes (source, data, source->length - nread);
        if (nread == -1) {
            if (header)
                vpix_free_header (header);
            return (-1);
        }
        if (nread == 0)
            break;
        data += nread;
    }
    source->data = header->data;
    source->is_pipe = 0;
    source->header_bytes = header;
    vpix_set_header_data (source);
    return (0);
}