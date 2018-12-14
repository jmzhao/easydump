class Loader :
    def load(self, type_var) :
        return getattr(self, 'load_%s'%(type(type_var).__name__))(type_var)

class Dumper :
    def dump(self, value) :
        try :
            return getattr(self, 'dump_%s'%(type(value).__name__))(value)
        except AttributeError as e :
            for base in (tuple, list, dict) :
                if isinstance(value, base) :
                    return getattr(self, 'dump_%s'%(base.__name__))(value)
            raise e


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
