import easydump

l = [1, 2, 3]
nested = {
    1 : [1.2, 3.4, 5.6],
    9 : [],
    15 : [4.0],
}

with open('./out_list.txt', 'w') as fout :
    dumper = easydump.TXTDumper(fout)
    dumper.dump(l)
with open('./out_list.txt', 'r') as fin :
    loader = easydump.TXTLoader(fin)
    l2 = loader.load(l)
assert(l == l2)

with open('./out_nested.txt', 'w') as fout :
    dumper = easydump.TXTDumper(fout)
    dumper.dump(nested)
with open('./out_nested.txt', 'r') as fin :
    loader = easydump.TXTLoader(fin)
    nested2 = loader.load(nested)
assert(nested == nested2)

with open('./out_list.bin', 'bw') as fout :
    dumper = easydump.BINDumper(fout)
    dumper.dump(l)
with open('./out_list.bin', 'br') as fin :
    loader = easydump.BINLoader(fin)
    l2 = loader.load(l)
assert(l == l2)

with open('./out_nested.bin', 'bw') as fout :
    dumper = easydump.BINDumper(fout)
    dumper.dump(nested)
with open('./out_nested.bin', 'br') as fin :
    loader = easydump.BINLoader(fin)
    nested2 = loader.load(nested)
assert(nested == nested2)
