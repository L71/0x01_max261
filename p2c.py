
# python list -> C data type printer
def print_c_list(datatype, varname, data, extra='') :

    datasize=len(data)
    # defaults print parameters...
    cols=8 # insert line break every N lines in data output
    formatstr='{:#9x}' # default printout format 8 pos Hex.
    c=0
    
    # setup for specific data types
    if datatype == 'uint32_t' or datatype == 'int32_t' :
        formatstr='{:#11x}'
        cols=6
    elif datatype == 'uint16_t' or datatype == 'int16_t' :
        formatstr='{:#7x}'
        cols=8
    elif datatype == 'uint8_t' or datatype == 'int8_t' :
        formatstr='{:#5x}'
        cols=12
    
    # print C definition:
    print datatype, varname+'['+str(datasize)+']'+extra+' = {'
    for i, e in enumerate(data) :
        # print e,
        print formatstr.format(e),
        if i < datasize-1 :
            print ',',
        c = c+1
        if c == cols :
            print ''
            c=0
    print '};'
    
# python 2D arrays to C data type printer
def print_c_2d_array(datatype, varname, data, extra='') :

    datasize=len(data) # length of dimension #1 ...
    elementsize=len(data[0]) # size of element #1. Must be same for all!
    # defaults print parameters...
    cols=8 # insert line break every N lines in data output
    formatstr='{:#9x}' # default printout format 8 pos Hex.
    c=0
    
    # setup for specific data types
    if datatype == 'uint32_t' or datatype == 'int32_t' :
        formatstr='{:#11x}'
        cols=6
    elif datatype == 'uint16_t' or datatype == 'int16_t' :
        formatstr='{:#7x}'
        cols=8
    elif datatype == 'uint8_t' or datatype == 'int8_t' :
        formatstr='{:#5x}'
        cols=12
    
    
    # print C definition:
    print datatype, varname+'['+str(datasize)+']['+str(elementsize)+extra+'] = {',
    for ii, element in enumerate(data) :
        print '{'
        for i, e in enumerate(element) :
            # print e,
            print formatstr.format(e),
            if i < elementsize-1 :
                print ',',
            c = c+1
            if c == cols :
                print ''
                c=0
        print '}',
        if ii < datasize-1:
            print ',',
    print '};'
    