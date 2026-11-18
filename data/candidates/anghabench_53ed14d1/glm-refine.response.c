unsigned int __cdecl mv78xx0_mbus_win_cfg_offset(int win)
{
    if (win < 8)
        return 16 * win;
    else
        return 16 * (win - 8) + 2304;
}