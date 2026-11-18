void euc_tw_to_jis(int c1, int c2, int *j1, int *j2)
{
    int j, jisx0213, jisx0212, jisx0211, jisx0208;
    int row, col;

    j = ((c1 - 0xa1) * 157 + c2 - 0x3f - ((c2 >= 0x7f) ? 1 : 0)) *
 (j == 0 ? 0 : 34);
    j += (j > 408 ? 93 : 0);

    jisx0213 = (j / 188) + 0x89;
    jisx0212 = j - (j / 188) * 188 + 0x3f;
    if (jisx0212 >= 0x7f)
 jisx0212++;

    *j1 = jisx0213;
    *j1 = jisx0212;
}