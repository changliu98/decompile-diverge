void __cdecl fill_row_type_widths(
        int StringsHeapIndexLength,
        int GUIDHeapIndexLength,
        int BlobHeapIndexLength,
        int *RowTypeWidths)
{
  *RowTypeWidths = 3 * GUIDHeapIndexLength + StringsHeapIndexLength + 2;
  RowTypeWidths[1] = 2 * StringsHeapIndexLength + 2;
  RowTypeWidths[2] = 2 * StringsHeapIndexLength + 10;
  RowTypeWidths[3] = 0;
  RowTypeWidths[4] = BlobHeapIndexLength + StringsHeapIndexLength + 2;
  RowTypeWidths[5] = 0;
  RowTypeWidths[6] = BlobHeapIndexLength + StringsHeapIndexLength + 10;
  RowTypeWidths[7] = 0;
  RowTypeWidths[8] = StringsHeapIndexLength + 4;
  RowTypeWidths[9] = 4;
  RowTypeWidths[10] = BlobHeapIndexLength + StringsHeapIndexLength + 2;
  RowTypeWidths[11] = BlobHeapIndexLength + 4;
  RowTypeWidths[12] = BlobHeapIndexLength + 4;
}