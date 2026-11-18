strtol_error parse_block_size(char *size_spec, int *options, uintmax_t *size)
{
    // Parse the human-readable block size specification and store the result in block_size
    strtol_error error = parse_human_block(size_spec, size, options);
    // If the parsed block size is zero, use the default block size and mark as invalid
    if (*size == 0) {
        *size = get_default_size();
        error = PARSE_ERROR_INVALID;
    }
    // Return the error status from parsing
    return error;
}