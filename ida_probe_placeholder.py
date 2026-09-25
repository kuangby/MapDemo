import idapro

idapro.open_database(r"G:\APP\game\mcbe\IDA\project\26.51_client.i64", False)

import ida_auto

ida_auto.auto_wait()

import ida_funcs
import ida_hexrays
import idautils

print("=== strings: client_request_placeholder ===")
str_eas = []
for s in idautils.Strings():
    if "client_request_placeholder" in str(s):
        str_eas.append(s.ea)
        print(hex(s.ea), repr(str(s)))

print("=== xrefs to those strings ===")
func_eas = set()
for sea in str_eas:
    for x in idautils.XrefsTo(sea):
        f = ida_funcs.get_func(x.frm)
        name = ida_funcs.get_func_name(f.start_ea) if f else "??"
        print(hex(x.frm), "in", name)
        if f:
            func_eas.add(f.start_ea)

print("=== names containing placeholder (ci) ===")
for ea, name in idautils.Names():
    if "placeholder" in name.lower():
        print(hex(ea), name)

print("=== func names: fullyloaded / isloaded ===")
for ea, name in idautils.Names():
    ln = name.lower()
    if ("fullyloaded" in ln or ("isloaded" in ln and "chunk" in ln)) and ida_funcs.get_func(ea):
        print(hex(ea), name)

print("=== decompile funcs referencing the string ===")
for fea in sorted(func_eas):
    try:
        cf = ida_hexrays.decompile(fea)
        print("-----", ida_funcs.get_func_name(fea), hex(fea))
        print(str(cf)[:4000])
    except Exception as e:
        print("decompile failed", hex(fea), e)

idapro.close_database(False)
print("DONE")
