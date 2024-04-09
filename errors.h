#ifndef ERRORS_H
#define ERRORS_H

#define FILE_OPEN_ERROR "File opening error"
#define FILE_READ_ERROR "File reading error"
#define FILE_LOAD_ERROR "File loading error"
#define READ_ERROR "Read error line"
#define FILE_LOAD_SUCCESS "File loaded successfully"
#define ZERO_ROWS_ERROR "Zero rows with viable data found"
#define FILE_NOT_SELECTED "File was not selected"
#define COLUMN_ERROR "Column index is non viable"
#define REGION_ERROR "Region name is non viable"
#define NO_CALCULATION_DATA "No viable Table Data exist"

enum Errors
{
    NoErrors,
    NoErrorsFileLoaded,
    FileNotSelected,
    FileLoadError,
    FileOpenError,
    FileReadError,
    ZeroRowsError,
    NoCalculationData,
    ColumnError,
    RegionError

};

#endif // ERRORS_H
