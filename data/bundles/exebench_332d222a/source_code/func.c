
void fill_row_type_widths(int StringsHeapIndexLength,
                                           int GUIDHeapIndexLength,
                                           int BlobHeapIndexLength,
                                           int RowTypeWidths[13]) {
  RowTypeWidths[0] = 2 + StringsHeapIndexLength + (GUIDHeapIndexLength * 3);
  RowTypeWidths[1] = 2 + (StringsHeapIndexLength * 2);
  RowTypeWidths[2] = 10 + (StringsHeapIndexLength * 2);
  RowTypeWidths[3] = 0;
  RowTypeWidths[4] = 2 + StringsHeapIndexLength + BlobHeapIndexLength;
  RowTypeWidths[5] = 0;
  RowTypeWidths[6] = 10 + StringsHeapIndexLength + BlobHeapIndexLength;
  RowTypeWidths[7] = 0;
  RowTypeWidths[8] = 4 + StringsHeapIndexLength;
  RowTypeWidths[9] = 4;
  RowTypeWidths[10] = 2 + StringsHeapIndexLength + BlobHeapIndexLength;
  RowTypeWidths[11] = 4 + BlobHeapIndexLength;
  RowTypeWidths[12] = 4 + BlobHeapIndexLength;
}
