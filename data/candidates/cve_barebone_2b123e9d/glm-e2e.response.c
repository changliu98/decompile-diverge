int writefile(const char *filename, struct file_data *data) {
    int ret = -1;
    int status = 0;
    FILE *fp;

    fp = fopen(filename, "wb"); // Assuming "wb" or similar mode at 0x2009
    if (fp == NULL) {
        warn("fopen: %s", filename); // Assuming format string at 0x200b
        ret = -1;
        goto end;
    }

    // fwrite(data->data, 1, data->size, fp)
    size_t written = fwrite((char*)data + 8, 1, data->size, fp);
    
    if (written == data->size) {
        if (fflush(fp) == 0) {
            // Success path
        } else {
            warn("fwrite/fflush: %s", filename); // Assuming format string at 0x2014
            status = -1;
        }
    } else {
        warn("fwrite/fflush: %s", filename);
        status = -1;
    }

    fclose(fp);
    ret = status;

end:
    return ret;
}