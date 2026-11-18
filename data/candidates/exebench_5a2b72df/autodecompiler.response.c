void ring(LPC_ENET_T *pENET)
{

 pENET->DMA_REC_POLL_DEMAND = 1;
}