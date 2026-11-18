void transformBlock(unsigned char block)
{

   idctRows();
   idctCols();


   switch (gScanType)
   {

   case PJPG_GRAYSCALE:
      copyY(0);
      break;


   case PJPG_YH1V1:
      if (block == 0)
         copyY(0);
      else if (block == 1)
         convertCb(0);
      else if (block == 2)
         convertCr(0);
      break;


   case PJPG_YH2V1:
      if (block == 0)
         copyY(0);
      else if (block == 1)
         copyY(64);
      else if (block == 2)
      {
         upsampleCbH(0, 0);
         upsampleCbH(4, 64);
      }
      break;


   case PJPG_YH1V2:
      if (block == 0)
         copyY(0);
      else if (block == 1)
         copyY(128);
      else if (block == 2)
      {
         upsampleCbV(0, 0);
         upsampleCbV(32, 128);
      }
      else if (block == 3)
      {
         upsampleCrV(0, 0);
         upsampleCrV(32, 128);
      }
      break;


   case PJPG_YH2V2:
      if (block == 0)
         copyY(0);
      else if (block == 1)
         copyY(64);
      else if (block == 2)
         copyY(128);
      else if (block == 3)
         copyY(192);
      else if (block == 4)
      {
         upsampleCb(0, 0);
         upsampleCb(4, 64);
         upsampleCb(32, 128);
         upsampleCb(48, 192);
      }
      else if (block == 5)
      {
         upsampleCr(0, 0);
         upsampleCr(4, 64);
         upsampleCr(32, 128);
         upsampleCr(48, 192);
      }
      break;
   }
}