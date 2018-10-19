import easydump

l = [1, 2, 3]
nested = {
    1 : [1.2, 3.4, 5.6],
    9 : [],
    15 : [4.0],
}

with open('./out_list.txt', 'w') as fout :
    dumper = easydump.txt.TXTDumper(fout)
    dumper.dump(l)
with open('./out_list.txt', 'r') as fin :
    loader = easydump.txt.TXTLoader(fin)
    l2 = loader.load(l)
assert(l == l2)

with open('./out_nested.txt', 'w') as fout :
    easydump.txt.dump(nested, fout)
with open('./out_nested.txt', 'r') as fin :
    nested2 = easydump.txt.load(nested, fin)
assert(nested == nested2)

with open('./out_list.bin', 'bw') as fout :
    dumper = easydump.bin.BINDumper(fout)
    dumper.dump(l)
with open('./out_list.bin', 'br') as fin :
    loader = easydump.bin.BINLoader(fin)
    l2 = loader.load(l)
assert(l == l2)

with open('./out_nested.bin', 'bw') as fout :
    easydump.bin.dump(nested, fout)
with open('./out_nested.bin', 'br') as fin :
    nested2 = easydump.bin.load(nested, fin)
assert(nested == nested2)
