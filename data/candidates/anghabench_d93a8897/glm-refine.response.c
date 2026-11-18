uint32_t __cdecl REG_A3XX_GRAS_CL_USER_PLANE_X(uint32_t plane_idx)
{
    return 0xCA0 + (plane_idx * 4);
}