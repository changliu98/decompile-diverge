void __cdecl fill_row_type_widths(
        int StringsHeapIndexLength,
        int GUIDHeapIndexLength,
        int BlobHeapIndexLength,
        int *RowTypeWidths)
{
    // RowTypeWidths[0] = Module
    *RowTypeWidths = (3 * GUIDHeapIndexLength) + StringsHeapIndexLength + 2;

    // RowTypeWidths[1] = TypeRef
    *(RowTypeWidths + RowType_TypeRef) = (2 * StringsHeapIndexLength) + 2;

    // RowTypeWidths[2] = TypeDef
    *(RowTypeWidths + RowType_TypeDef) = (2 * StringsHeapIndexLength) + 10;

    // RowTypeWidths[3] = FieldPtr (Reserved)
    *(RowTypeWidths + RowType_FieldPtr) = 0;

    // RowTypeWidths[4] = Field
    *(RowTypeWidths + RowType_Field) = BlobHeapIndexLength + StringsHeapIndexLength + 2;

    // RowTypeWidths[5] = MethodPtr (Reserved)
    *(RowTypeWidths + RowType_MethodPtr) = 0;

    // RowTypeWidths[6] = MethodDef
    *(RowTypeWidths + RowType_Method) = BlobHeapIndexLength + StringsHeapIndexLength + 10;

    // RowTypeWidths[7] = ParamPtr (Reserved)
    *(RowTypeWidths + RowType_ParamPtr) = 0;

    // RowTypeWidths[8] = Param
    *(RowTypeWidths + RowType_Param) = StringsHeapIndexLength + 4;

    // RowTypeWidths[9] = InterfaceImpl
    *(RowTypeWidths + RowType_InterfaceImpl) = 4;

    // RowTypeWidths[10] = MemberRef
    *(RowTypeWidths + RowType_MemberRef) = BlobHeapIndexLength + StringsHeapIndexLength + 2;

    // RowTypeWidths[11] = Constant
    *(RowTypeWidths + RowType_Constant) = BlobHeapIndexLength + 4;

    // RowTypeWidths[12] = CustomAttribute
    *(RowTypeWidths + RowType_CustomAttribute) = BlobHeapIndexLength + 4;
}