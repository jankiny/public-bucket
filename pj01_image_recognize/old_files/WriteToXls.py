import xlwt
import numpy as np

def write_list_to_xls( filename, sheetname, rows, columns, data_list ) :
    '''input: filename, sheetname, rows, columns, data_list '''
    data_list = np.asarray(data_list).reshape(rows,columns)

    workbook = xlwt.Workbook(encoding='ascii')
#    worksheet = workbook.add_sheet(sheetname, cell_overwrite_ok=True)
    worksheet = workbook.add_sheet(sheetname)
    for row in range(rows):
        for column in range(columns):
            worksheet.write(row, column, data_list[row][column])

    filename += '.xls'
    workbook.save(filename)

    pass

