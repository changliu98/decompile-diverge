int ui_select(int tcp_sck)
{
    if (g_tcp_sck == 0)
        g_tcp_sck = tcp_sck;

    return 1;
}