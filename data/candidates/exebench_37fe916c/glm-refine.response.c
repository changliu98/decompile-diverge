int stream_open(const char *filename, int rwmode, int *handle) 
{
    // Parameters 'filename' and 'rwmode' are ignored in this stub.
    // Unconditionally assign a dummy handle and return 0 (success).
    if (handle != NULL) {
        *handle = 1;
    }
    
    return 0;
}