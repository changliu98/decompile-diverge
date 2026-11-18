void LCD_Clear(u8 Page)
{
  u8 Page1 = 0, Column = 0;


  LCD_SetMasterPage(15);
  LCD_SetSlavePage(15);

  LCD_SetMasterColumn(0);
  LCD_SetSlaveColumn(0);

  for (Page1=0; Page1<4; Page1++)
  {

    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
    LCD_SendSlaveData(0x00);
  }

  LCD_SetMasterColumn(0);
  LCD_SetSlaveColumn(0);

  for (Page1=0; Page1<4; Page1++)
  {

    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
    LCD_SendMasterData(0x00);
  }
}