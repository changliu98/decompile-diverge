static int _set_clock_prescaler(TIM_TypeDef *TIMx, int ps)
{
 TIMx->PSC &= ~0x000e;
 TIMx->PSC |= ps & 0x0e;
 return TIMx->PSC;
}