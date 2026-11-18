static void transformBlock(uint8 mcuBlock)
{
   idctRows();
   idctCols();
   
   switch (gScanType)
   {
      case PJPG_GRAYSCALE:
      {
         // MCU size: 1, 1 block per MCU
         copyY(0);
         break;
      }
      case PJPG_YH1V1:
      {
         // MCU size: 8x8, 3 blocks per MCU
         switch (mcuBlock)
         {
            case 0:
            {
               copyY(0);
               break;
            }
            case 1:
            {
               convertCb(0);
               break;
            }
            case 2:
            {
               convertCr(0);
               break;
            }
         }

         break;
      }
      case PJPG_YH1V2:
      {
         // MCU size: 8x16, 4 blocks per MCU
         switch (mcuBlock)
         {
            case 0:
            {
               copyY(0);
               break;
            }
            case 1:
            {
               copyY(128);
               break;
            }
            case 2:
            {
               upsampleCbV(0, 0);
               upsampleCbV(4*8, 128);
               break;
            }
            case 3:
            {
               upsampleCrV(0, 0);
               upsampleCrV(4*8, 128);
               break;
            }
         }

         break;
      }        
      case PJPG_YH2V1:
      {
         // MCU size: 16x8, 4 blocks per MCU
         switch (mcuBlock)
         {
            case 0:
            {
               copyY(0);
               break;
            }
            case 1:
            {
               copyY(64);
               break;
            }
            case 2:
            {
               upsampleCbH(0, 0);
               upsampleCbH(4, 64);
               break;
            }
            case 3:
            {
               upsampleCrH(0, 0);
               upsampleCrH(4, 64);
               break;
            }
         }
         
         break;
      }        
      case PJPG_YH2V2:
      {
         // MCU size: 16x16, 6 blocks per MCU
         switch (mcuBlock)
         {
            case 0:
            {
               copyY(0);
               break;
            }
            case 1:
            {
               copyY(64);
               break;
            }
            case 2:
            {
               copyY(128);
               break;
            }
            case 3:
            {
               copyY(192);
               break;
            }
            case 4:
            {
               upsampleCb(0, 0);
               upsampleCb(4, 64);
               upsampleCb(4*8, 128);
               upsampleCb(4+4*8, 192);
               break;
            }
            case 5:
            {
               upsampleCr(0, 0);
               upsampleCr(4, 64);
               upsampleCr(4*8, 128);
               upsampleCr(4+4*8, 192);
               break;
            }
         }

         break;
      }         
   }      
}