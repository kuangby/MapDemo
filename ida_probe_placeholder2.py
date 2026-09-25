import idapro

idapro.open_database(r"G:\APP\game\mcbe\IDA\project\26.51_client.i64", False)

import ida_auto

ida_auto.auto_wait()

import ida_funcs
import ida_hexrays
import ida_name
import idautils


def decompile_at(ea, limit=6000):
    try:
        cf = ida_hexrays.decompile(ea)
        return str(cf)[:limit] if cf else "<no pseudocode>"
    except Exception as e:
        return f"<decompile failed: {e}>"


def find_func(name_substr):
    for ea, name in idautils.Names():
        if name_substr in name and ida_funcs.get_func(ea):
            return ea, name
    return None, None


# 1. SubChunk::isPlaceHolderSubChunk
ea, name = find_func("isPlaceHolderSubChunk@SubChunk")
print("=====", name, hex(ea))
print(decompile_at(ea))

print("===== callers of isPlaceHolderSubChunk =====")
callers = set()
for x in idautils.XrefsTo(ea):
    f = ida_funcs.get_func(x.frm)
    if f:
        callers.add(f.start_ea)
        print(hex(x.frm), "in", ida_funcs.get_func_name(f.start_ea))

for c in sorted(callers):
    print("----- caller", ida_funcs.get_func_name(c), hex(c))
    print(decompile_at(c, 3000))

# 2. LevelChunk::setEmptyClientChunk
ea2, name2 = find_func("setEmptyClientChunk")
print("=====", name2, hex(ea2))
print(decompile_at(ea2, 4000))

# 3. LevelChunk::setClientNeedsToRequestSubchunks
ea3, name3 = find_func("setClientNeedsToRequestSubchunks")
print("=====", name3, hex(ea3))
print(decompile_at(ea3, 3000))

idapro.close_database(False)
print("DONE")
