import struct

import pytest

from ddiv.state import blob, crash_signature, observations, symbol_states


def snapshot(data, bss=b""):
    return b"DDIV1\0\0\0" + struct.pack("<QQ", len(data), len(bss)) + data + bss


def test_reordered_globals_and_linker_padding_do_not_differ():
    left = symbol_states(snapshot(b"\x01\0\0\0\x02\0\0\0"),
                         {"sizes": [8, 0], "symbols": {"a": [0, 4], "b": [4, 4]}, "relocations": []})
    right = symbol_states(snapshot(b"\x02\0\0\0xxxx\x01\0\0\0"),
                          {"sizes": [12, 0], "symbols": {"b": [0, 4], "a": [8, 4]}, "relocations": []})
    assert left == right
    assert left["a"]["signed_le"] == 1


def test_relocated_pointer_slots_are_masked_but_adjacent_values_remain_visible():
    layout = {"sizes": [12, 0], "symbols": {"ptr": [0, 8], "value": [8, 4]}, "relocations": [[0, 8]]}
    left = symbol_states(snapshot(struct.pack("<QI", 0x401000, 42)), layout)
    right = symbol_states(snapshot(struct.pack("<QI", 0x407000, 43)), layout)
    assert left["ptr"]["sha256"] == right["ptr"]["sha256"]
    assert left["ptr"]["raw_hex"] != right["ptr"]["raw_hex"]
    assert left["value"]["sha256"] != right["value"]["sha256"]


def test_truncated_snapshot_is_an_error_even_with_no_globals():
    layout = {"sizes": [4, 0], "symbols": {}, "relocations": []}
    assert symbol_states(snapshot(bytes(4)), layout) == {}
    with pytest.raises(ValueError, match="truncated"):
        symbol_states(snapshot(bytes(4))[:-1], layout)


def test_hash_covers_bytes_beyond_preview_and_preserves_output_addresses():
    assert blob(b"a" * 1024 + b"x")["sha256"] != blob(b"a" * 1024 + b"y")["sha256"]
    assert blob(b"0x1234")["sha256"] != blob(b"0x5678")["sha256"]


def test_crash_identity_ignores_coordinates_but_compares_access_direction():
    log = "ERROR: AddressSanitizer: heap-buffer-overflow\nREAD of size 1\n    #0 0x401023 in target a.c:10:2\n"
    other = log.replace("0x401023", "0x501039").replace("a.c:10:2", "b.c:99:7")
    assert crash_signature(log, -6) == crash_signature(other, -6)
    assert crash_signature(log, -6) != crash_signature(log.replace("READ", "WRITE"), -6)
    assert crash_signature("", 139) is None
    assert crash_signature("", -11) == {"kind": "signal", "signal": 11}


def test_last_explicit_observation_is_poststate_and_partial_records_fail():
    first = struct.pack("<QQ", 3, 1) + b"out" + b"a"
    last = struct.pack("<QQ", 3, 1) + b"out" + b"b"
    assert observations(first + last)["out"]["hex"] == "62"
    with pytest.raises(ValueError, match="truncated"):
        observations(first + last[:-1])
