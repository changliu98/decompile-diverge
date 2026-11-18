unsigned int create_ce_flags(unsigned int stage)
{
    // Shift the stage value into the correct bit position to create stage flags
    return stage << CE_STAGESHIFT;
}