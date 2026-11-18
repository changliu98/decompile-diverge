static int is_ip_error(int error)
{
    return (error - 128 < 5);
}