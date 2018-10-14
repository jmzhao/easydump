from collections import namedtuple

class OStream :
    def __init__(self, o) :
        self.o = o
    def write(self, x) :
        return self.o.write(x)

class IStream :
    def __init__(self, i) :
        self.i = i
        self.stream_iter = iter(IStream.tokens(i))
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
    def load_int(self, x) :
        return self._load(x)
    def load_float(self, x) :
        return self._load(x)
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
    def dump_int(self, x) :
        return self._dump(x)
    def dump_float(self, x) :
        return self._dump(x)
    def dump_tuple(self, x) :
        return tuple(self.dump(xi) for xi in x)
    def dump_list(self, x) :
        n = self.dump_int(int(len(x)))
        return list(self.dump(xi) for xi in x)
    def dump_dict(self, x) :
        n = self.dump_int(int(len(x)))
        return dict(self.dump(xi) for xi in x.items())


class TXTBaseLoader :
    def _load(self, type_val) :
        return type(type_val)(self.stream.read())

class TXTBaseDumper :
    def _dump(self, value) :
        self.stream.write(str(value))
        self.stream.write(' ')

class TXTLoader (Loader, CompactLoading, TXTBaseLoader) :
    def __init__(self, stream) :
        self.stream = stream

class TXTDumper (Dumper, CompactDumping, TXTBaseDumper) :
    def __init__(self, stream) :
        self.stream = stream
