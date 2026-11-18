int subprocess_error_from_errno(int err)
{
    switch (err) {
    case 1:
    case 13:
        return -5;
    case 2:
    case 20:
        return -4;
    case 12:
    case 23:
    case 24:
        return -6;
    default:
        return -1;
    }
}