import easydump

l = [1, 2, 3]
nested = {
    1 : [1.2, 3.4, 5.6],
    9 : [],
    15 : [4.0],
}

with open('./out_list.txt', 'w') as fout :
    dumper = easydump.TXTDumper(easydump.OStream(fout))
    dumper.dump(l)
with open('./out_list.txt', 'r') as fin :
    loader = easydump.TXTLoader(easydump.IStream(fin))
    l2 = loader.load(l)
assert(l == l2)

with open('./out_nested.txt', 'w') as fout :
    dumper = easydump.TXTDumper(easydump.OStream(fout))
    dumper.dump(nested)
with open('./out_nested.txt', 'r') as fin :
    loader = easydump.TXTLoader(easydump.IStream(fin))
    nested2 = loader.load(nested)
assert(nested == nested2)
