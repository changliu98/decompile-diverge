void nova_posicao(pacman_t *pacman, coordenadas_t *nova, int x, int y)
{
 int linha, coluna;
 linha = pacman->pos_atual.linha + x;
 coluna = pacman->pos_atual.coluna + y;

 nova->linha = linha;
 nova->coluna = coluna;
}