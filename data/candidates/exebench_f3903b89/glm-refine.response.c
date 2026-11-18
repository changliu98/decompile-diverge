void __cdecl get_payload_info(char *bzimage, int *offset, int *size)
{
    // Cast the base pointer to an unsigned 32-bit integer pointer 
    // to accurately reflect memory access without sign-extension issues.
    unsigned int *image_hdr = (unsigned int *)bzimage;

    // bzimage[497] corresponds to the 'setup_sects' field in the Linux boot header.
    // The payload offset is calculated as:
    // (payload_offset field) + ((setup_sects + 1) * 512)
    // Note: ((unsigned __int8)(bzimage[497] + 1) << 9) safely handles the 8-bit wraparound 
    // (e.g., if setup_sects is 0xFF, 0xFF + 1 wraps to 0x00).
    *offset = image_hdr[146] + ((unsigned char)(bzimage[497] + 1) << 9);
    
    // image_hdr[147] corresponds to the 'payload_length' field in the Linux boot header.
    *size = image_hdr[147];
}