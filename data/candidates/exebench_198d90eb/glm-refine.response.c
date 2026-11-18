void __cdecl advance_kpos(KeyPositions *kpos)
{
    kpos->pos1 = (kpos->pos1 + 1) % 41;
    kpos->pos2 = (kpos->pos2 + 1) % 31;
    kpos->pos3 = (kpos->pos3 + 1) % 29;
    kpos->pos4 = (kpos->pos4 + 1) % 26;
    kpos->pos5 = (kpos->pos5 + 1) % 23;
}