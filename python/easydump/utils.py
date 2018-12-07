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

def parse_typestring(s) :
    '''parse a type string into a type var which is expected by `smart_load`.

    Examples:
    >>> parse_typestring('list(int)')
    [0]

    >>> parse_typestring('map(id, id)')
    {0: 0}

    >>> parse_typestring('list(tuple(id, double))')
    [(0, 0.0)]

    >>> parse_typestring('map(id, list(id))')
    {0: [0]}
    '''
    def list(x) :
        return [x]
    def tuple(*x) :
        return x
    def map(a, b) :
        return {a : b}
    int = 0
    id = 0
    string = ''
    double = 0.0
    return eval(s)

def gen_typestring(v) :
    '''generate type string from a variable, the reverse operation of `parse_typestring`.

    Examples:
    >>> gen_typestring([3, 4, 5])
    'list(int)'

    >>> gen_typestring({3: 4, 5: 6})
    'map(int,int)'

    >>> gen_typestring([(1, 2.2), (3, 4.4), (5, 6.6)])
    'list(tuple(int,double))'

    >>> gen_typestring({3: [1, 2, 3], 5: [7, 8, 9]})
    'map(int,list(int))'
    '''
    if isinstance(v, list) :
        return 'list({})'.format(gen_typestring(v[0]))
    elif isinstance(v, tuple) :
        return 'tuple({})'.format(','.join(gen_typestring(x) for x in v))
    elif isinstance(v, dict) :
        a, b = next(iter(v.items()))
        return 'map({},{})'.format(gen_typestring(a), gen_typestring(b))
    elif isinstance(v, float) :
        return 'double'
    elif isinstance(v, int) :
        return 'int'
    else :
        raise ValueError("Value type '{}' not supported.".format(type(v)))


if __name__ == "__main__":
    import doctest
    doctest.testmod()
