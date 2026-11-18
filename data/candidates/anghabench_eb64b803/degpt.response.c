int file_type_to_content_type(int file_type_code)
{
    switch(file_type_code) {
    case 0x80:
        return ct_webp;
    case 0x81:
        return ct_unknown;
    case 0x82:
        return ct_png;
    case 0x83:
        return ct_pdf;
    case 0x84:
        return ct_partial;
    case 0x85:
        return ct_mp4;
    case 0x86:
        return ct_mp3;
    case 0x87:
        return ct_mov;
    case 0x88:
        return ct_jpeg;
    case 0x89:
        return ct_gif;
    default:
        return ct_last | 0x40000000;
    }
}