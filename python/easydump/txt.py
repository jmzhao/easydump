from .common import CompactDumping, CompactLoading, Dumper, Loader


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


def load(type_var, fp, _Loader = TXTLoader) :
    return _Loader(fp).load(type_var)

def dump(value, fp, _Dumper = TXTDumper) :
    return _Dumper(fp).dump(value)
