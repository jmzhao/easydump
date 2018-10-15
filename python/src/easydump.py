from collections import namedtuple


class TXTIStream :
    def __init__(self, i) :
        self.i = i
        self.stream_iter = iter(self.__class__.tokens(i))
    @staticmethod
    def tokens(io) :
        for line in io :
            for token in line.strip().split() :
                yield token
    def read(self) :
        return next(self.stream_iter)


class Loader :
    def load(self, type_var) :
        return getattr(self, 'load_%s'%(type(type_var).__name__))(type_var)

class Dumper :
    def dump(self, value) :
        return getattr(self, 'dump_%s'%(type(value).__name__))(value)


class CompactLoading :
    def load_tuple(self, x) :
        return tuple(self.load(xi) for xi in x)
    def load_list(self, x) :
        n = self.load_int(int())
        t = x[0]
        return list(self.load(t) for _ in range(n))
    def load_dict(self, x) :
        n = self.load_int(int())
        t = next(iter(x.items()))
        return dict(self.load(t) for _ in range(n))

class CompactDumping :
    def dump_tuple(self, x) :
        return tuple(self.dump(xi) for xi in x)
    def dump_list(self, x) :
        n = self.dump_int(int(len(x)))
        return list(self.dump(xi) for xi in x)
    def dump_dict(self, x) :
        n = self.dump_int(int(len(x)))
        return dict(self.dump(xi) for xi in x.items())


class TXTBaseLoader :
    def load_int(self, _) :
        return int(self.stream.read())
    def load_float(self, _) :
        return float(self.stream.read())

class TXTBaseDumper :
    def _dump(self, value) :
        self.stream.write(str(value))
        self.stream.write(' ')
    def dump_int(self, value) :
        self._dump(value)
    def dump_float(self, value) :
        self._dump(value)

class TXTLoader (Loader, CompactLoading, TXTBaseLoader) :
    def __init__(self, fp, stream_wrapper = TXTIStream) :
        self.stream = stream_wrapper(fp) if stream_wrapper else fp

class TXTDumper (Dumper, CompactDumping, TXTBaseDumper) :
    def __init__(self, fp, stream_wrapper = None) :
        self.stream = stream_wrapper(fp) if stream_wrapper else fp


import struct

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
