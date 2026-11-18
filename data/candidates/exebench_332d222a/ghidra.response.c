void fill_row_type_widths
               (int StringsHeapIndexLength,int GUIDHeapIndexLength,int BlobHeapIndexLength,
               int *RowTypeWidths)

{
  int *RowTypeWidths_local;
  int BlobHeapIndexLength_local;
  int GUIDHeapIndexLength_local;
  int StringsHeapIndexLength_local;
  
  *RowTypeWidths = StringsHeapIndexLength + 2 + GUIDHeapIndexLength * 3;
  RowTypeWidths[1] = StringsHeapIndexLength * 2 + 2;
  RowTypeWidths[2] = StringsHeapIndexLength * 2 + 10;
  RowTypeWidths[3] = 0;
  RowTypeWidths[4] = StringsHeapIndexLength + 2 + BlobHeapIndexLength;
  RowTypeWidths[5] = 0;
  RowTypeWidths[6] = StringsHeapIndexLength + 10 + BlobHeapIndexLength;
  RowTypeWidths[7] = 0;
  RowTypeWidths[8] = StringsHeapIndexLength + 4;
  RowTypeWidths[9] = 4;
  RowTypeWidths[10] = StringsHeapIndexLength + 2 + BlobHeapIndexLength;
  RowTypeWidths[0xb] = BlobHeapIndexLength + 4;
  RowTypeWidths[0xc] = BlobHeapIndexLength + 4;
  return;
}