int FNEGQ(uint64_t *rd, uint64_t *rs2)
{
    rd[0] = rs2[0] ^ 0x8000000000000000;
    rd[1] = rs2[1];

    return 1;
}