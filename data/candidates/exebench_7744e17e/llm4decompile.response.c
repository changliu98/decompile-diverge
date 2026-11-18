void ee_readn(uint32_t address, ee_readn_t *readn)
{
    if (address > 0x80)
    {
        readn->error = 0x1f6;
        return;
    }

    readn->error = 0x000;
    readn->data = 0x38000 + (address << 8);
}