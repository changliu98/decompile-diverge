int file_type_to_content_type(int file_type) {
    int content_type;
    
    // The switch handles values from 0x80 to 0x89 (inclusive)
    switch (file_type) {
        case 0x80: content_type = ct_unknown; break;
        case 0x81: content_type = ct_jpeg;    break;
        case 0x82: content_type = ct_gif;     break;
        case 0x83: content_type = ct_png;     break;
        case 0x84: content_type = ct_pdf;     break;
        case 0x85: content_type = ct_mp3;     break;
        case 0x86: content_type = ct_mov;     break;
        case 0x87: content_type = ct_mp4;     break;
        case 0x88: content_type = ct_partial; break;
        case 0x89: content_type = ct_webp;    break;
        default:
            // For values outside the 0x80-0x89 range
            content_type = ct_last | 0x40000000;
            break;
    }
    
    return content_type;
}