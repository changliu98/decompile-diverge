static unsigned F(unsigned x, unsigned y, unsigned rcon) {
  return (x & rcon) | (y & ~x);
# 110 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/willempx/verifast/refs/heads/master/examples/crypto_ccs/source/rijndael_simplified/rijndael_simplified.c"
}