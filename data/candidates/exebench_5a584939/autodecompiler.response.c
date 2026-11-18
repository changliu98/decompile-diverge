static int path_source_set(TIM_TypeDef *TIMx, int ps)
{
 TIMx->PSC &= ~0x000e;
 TIMx->PSC |= ps & 0x0e;
 return TIMx->PSC;
}