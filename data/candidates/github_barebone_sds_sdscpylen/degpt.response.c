sds sdscpylen(sds target_sds, char *source_str, size_t string_length)
{
    // Check if the current allocated memory is sufficient for the new string length
    if (sdsalloc(target_sds) < string_length) {
        // Make room for the new string by reallocating if necessary
        target_sds = sdsMakeRoomFor(target_sds, string_length - sdslen(target_sds));
        // If memory allocation fails, return NULL
        if (target_sds == NULL) {
            return NULL;
        }
    }
    // Copy the new string content into the SDS buffer
    memcpy(target_sds, source_str, string_length);
    // Null-terminate the string
    target_sds[string_length] = '\0';
    // Update the length field of the SDS string
    sdssetlen(target_sds, string_length);
    // Return the updated SDS string
    return target_sds;
}