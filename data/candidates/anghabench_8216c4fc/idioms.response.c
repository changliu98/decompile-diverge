static inline int create_ce_flags(int stage)
{
    return (stage << CE_STAGESHIFT);
}