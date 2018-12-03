from . import bin, txt

def smart_load(type_var, filename, filetype=None) :
    filetype = filetype or filename[-3:]
    if filetype == 'bin' :
        with open(filename, 'rb') as f :
            return bin.load(type_var, f)
    elif filetype == 'txt' :
        with open(filename, 'r') as f :
            return txt.load(type_var, f)
    else :
        raise ValueError("Not supported file type: '{}'".format(filename))

def smart_dump(var, filename, filetype=None) :
    filetype = filetype or filename[-3:]
    if filetype == 'bin' :
        with open(filename, 'wb') as f :
            return bin.dump(var, f)
    elif filetype == 'txt' :
        with open(filename, 'w') as f :
            return txt.dump(var, f)
    else :
        raise ValueError("Not supported file type: '{}'".format(filename))
