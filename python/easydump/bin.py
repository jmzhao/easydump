import struct

from .common import CompactDumping, CompactLoading, Dumper, Loader


struct_int = struct.Struct('i')
struct_float = struct.Struct('d')

class BINBaseLoader :
    def load_int(self, _) :
        return struct_int.unpack(self.stream.read(struct_int.size))[0]
    def load_float(self, _) :
        return struct_float.unpack(self.stream.read(struct_float.size))[0]

class BINBaseDumper :
    def dump_int(self, x) :
        return self.stream.write(struct_int.pack(x))
    def dump_float(self, x) :
        return self.stream.write(struct_float.pack(x))

class BINLoader (Loader, CompactLoading, BINBaseLoader) :
    def __init__(self, fp, stream_wrapper = None) :
        self.stream = stream_wrapper(fp) if stream_wrapper else fp

class BINDumper (Dumper, CompactDumping, BINBaseDumper) :
    def __init__(self, fp, stream_wrapper = None) :
        self.stream = stream_wrapper(fp) if stream_wrapper else fp


def load(type_var, fp, _Loader = BINLoader) :
    return _Loader(fp).load(type_var)

def dump(value, fp, _Dumper = BINDumper) :
    return _Dumper(fp).dump(value)
