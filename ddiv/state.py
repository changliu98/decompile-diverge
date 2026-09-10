"""Post-state comparison adapted from VanishBench's existing oracle.

See vanishbench/functional.py:symbol_digests_from and
oracle_aflpp/difffuzz_run_v3.py:{data_bss_symbol_offsets,relocated_windows,
symbol_digests,crash_signature,_filesystem_observation}. Keep the same clean
.data/.bss, by-name, relocation-masked comparison, but retain concrete bytes for
counterexamples. No benchmark imports or dataset assumptions are needed.
"""
import hashlib
import re
import stat
import struct
import subprocess
from pathlib import Path


def blob(data):
    """Hash ALL bytes; previews are only for display, never for comparison."""
    return {"size": len(data), "sha256": hashlib.sha256(data).hexdigest(),
            "hex": data[:256].hex(), "text": data[:256].decode("utf-8", "replace"),
            "preview_truncated": len(data) > 256}


def _tool(*args):
    return subprocess.check_output(args, text=True, timeout=30)


def elf_layout(binary, source_object):
    """Offsets in [.data][.bss], restricted to the user's writable symbols.

    The separate runtime object must not introduce compared state. --emit-relocs
    retains pointer slots even in non-PIE binaries; all ELF inspection is run in
    the same Docker image as the compiler, never using the host toolchain.
    """
    header = _tool("readelf", "-h", str(binary))
    if "ELF64" not in header or "little endian" not in header or "X86-64" not in header:
        raise ValueError("automatic global capture currently requires little-endian x86-64 ELF")
    wanted = set()
    for line in _tool("nm", "-S", "--defined-only", str(source_object)).splitlines():
        p = line.split()
        if len(p) == 4 and p[2] in "dDbBcC" and int(p[1], 16):
            wanted.add(p[3])
    bounds, symbols = {}, {}
    for line in _tool("nm", "-S", "--defined-only", str(binary)).splitlines():
        p = line.split()
        if len(p) == 3 and p[2] in ("__data_start", "_edata", "__bss_start", "_end"):
            bounds[p[2]] = int(p[0], 16)
        elif len(p) == 4 and p[3] in wanted:
            if p[3] in symbols:
                raise ValueError("ambiguous global symbol: " + p[3])
            symbols[p[3]] = (int(p[0], 16), int(p[1], 16))
    ds, de, bs, be = (bounds[n] for n in ("__data_start", "_edata", "__bss_start", "_end"))
    sizes = [de - ds, be - bs]

    def offset(addr, size):
        if ds <= addr and addr + size <= de:
            return addr - ds
        if bs <= addr and addr + size <= be:
            return sizes[0] + addr - bs
        return None

    offsets = {}
    for name, (addr, size) in symbols.items():
        off = offset(addr, size)
        if off is not None:
            offsets[name] = [off, size]
    windows = set()
    widths = {"R_X86_64_64": 8, "R_X86_64_RELATIVE": 8, "R_X86_64_GLOB_DAT": 8,
              "R_X86_64_JUMP_SLOT": 8, "R_X86_64_32": 4, "R_X86_64_32S": 4}
    for line in _tool("readelf", "-rW", str(binary)).splitlines():
        p = line.split()
        if len(p) < 3 or p[2] not in widths:
            continue
        off = offset(int(p[0], 16), widths[p[2]])
        if off is not None:
            windows.add((off, widths[p[2]]))
    return {"sizes": sizes, "symbols": offsets, "relocations": sorted(windows),
            "excluded_symbols": sorted(wanted - set(offsets))}


def symbol_states(dump, layout):
    """Same mask-and-slice semantics as the existing symbol_digests helper.

    A partial dump is an observation error, never an empty/equal state map.
    Empty maps ARE valid when the program has no writable globals.
    """
    if len(dump) < 24 or dump[:8] != b"DDIV1\0\0\0":
        raise ValueError("missing or invalid global snapshot header")
    sizes = list(struct.unpack("<QQ", dump[8:24]))
    if sizes != layout["sizes"] or len(dump) != 24 + sum(sizes):
        raise ValueError("truncated or incompatible global snapshot")
    data = dump[24:]
    out = {}
    for name, (off, size) in sorted(layout["symbols"].items()):
        if off < 0 or off + size > len(data):
            raise ValueError("global extends beyond snapshot: " + name)
        raw = data[off:off + size]
        masked = bytearray(raw)
        ranges = []
        for woff, width in layout["relocations"]:
            lo, hi = max(off, woff), min(off + size, woff + width)
            if lo < hi:
                masked[lo - off:hi - off] = bytes(hi - lo)
                ranges.append([lo - off, hi - off])
        value = blob(bytes(masked))
        value["raw_hex"] = raw[:256].hex()
        value["masked_ranges"] = ranges
        if size in (1, 2, 4, 8) and not ranges:
            value["unsigned_le"] = int.from_bytes(raw, "little")
            value["signed_le"] = int.from_bytes(raw, "little", signed=True)
        out[name] = value
    return out


def observations(data):
    out, pos = {}, 0
    while pos < len(data):
        if pos + 16 > len(data):
            raise ValueError("truncated explicit observation")
        nname, nbytes = struct.unpack("<QQ", data[pos:pos + 16])
        pos += 16
        if pos + nname + nbytes > len(data):
            raise ValueError("truncated explicit observation payload")
        name = data[pos:pos + nname].decode("utf-8", "strict")
        pos += nname
        out[name] = blob(data[pos:pos + nbytes])
        pos += nbytes
    return out


def filesystem(root):
    """Compare file bytes, names, modes, symlinks and directories, without mtimes."""
    out = {}
    # Path.rglob does not follow directory symlinks on the supported Python versions.
    for path in sorted(Path(root).rglob("*")):
        mode = path.lstat().st_mode
        item = {"mode": stat.S_IMODE(mode)}
        if stat.S_ISLNK(mode):
            item.update(kind="symlink", target=str(path.readlink()))
        elif stat.S_ISREG(mode):
            item.update(kind="file", **blob(path.read_bytes()))
        elif stat.S_ISDIR(mode):
            item["kind"] = "directory"
        else:
            item.update(kind="special", type=stat.S_IFMT(mode))
        out[str(path.relative_to(root))] = item
    return out


def crash_signature(log, returncode):
    """Weakness + access direction + faulting function, without line numbers.

    As in crashparse.patterns_match, a READ and WRITE at the same function are
    different manifestations. Ordinary exit(139) is not a SIGSEGV.
    """
    kind = None
    m = re.search(r"(?:ERROR: |SUMMARY: )AddressSanitizer:\s*(\S+)", log)
    if m:
        kind = "asan:" + m.group(1)
    else:
        m = re.search(r"runtime error:\s*([^\n]+)", log)
        if m:
            msg = m.group(1)
            known = ("signed integer overflow", "unsigned integer overflow", "division by zero",
                     "index", "load of misaligned address", "store to misaligned address",
                     "load of null pointer", "store to null pointer", "shift exponent",
                     "left shift of negative value", "left shift", "member access")
            kind = "ubsan:" + next((k for k in known if msg.startswith(k)),
                                      re.sub(r"0x[0-9a-fA-F]+|-?\d+|'[^']*'", "", msg))
    if kind is None:
        return {"kind": "signal", "signal": -returncode} if returncode < 0 else None
    access = re.search(r"\b(READ|WRITE) of size\b", log)
    if access is None:
        access = re.search(r"caused by a (READ|WRITE) memory access", log)
    function = None
    for match in re.finditer(r"^\s*#\d+\s+0x[0-9a-fA-F]+\s+in\s+(\S+)", log, re.M):
        fn = match.group(1)
        if fn.startswith(("__asan", "__ubsan", "__sanitizer", "__interceptor")):
            continue
        if fn in ("_start", "__libc_start_main", "__libc_start_call_main"):
            continue
        function = fn
        break
    return {"kind": kind, "access": access.group(1) if access else None, "function": function}


def channel_values(post):
    """Canonical values used for BOTH pair comparison and repeat confirmation."""
    out = {}
    for build in ("sanitized", "clean"):
        run = post[build]
        terminal = (run["status"], run["returncode"], run.get("crash"))
        out[build + ".termination"] = terminal
        if run["status"] == "exited":
            for name in ("stdout", "stderr"):
                value = run[name]
                out[build + "." + name] = (terminal, value["size"], value["sha256"])
            out[build + ".files"] = (terminal, run["files"])
    if post["clean"]["status"] == "exited" and post.get("globals") is not None:
        out["globals"] = {n: (v["size"], v["sha256"]) for n, v in post["globals"].items()}
        out["observations"] = {n: (v["size"], v["sha256"])
                               for n, v in post["observations"].items()}
    return out


def differences(left, right):
    a, b = channel_values(left), channel_values(right)
    # Missing normal-exit channels after a crash/hang are represented by the
    # termination difference, not falsely reported as empty/missing values.
    return [key for key in sorted(a.keys() & b.keys()) if a[key] != b[key]]
