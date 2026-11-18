static int REG_A5XX_RB_MRT_BUF_INFO(int button)
{
 return 0xe152 + button * 7;
}