
with open("D:\\repos\\MPP_KTRC\\build-btl\\KTRC_MPP_normal.bin", "rb") as f:
    fw_raw = f.read()

import hashlib
fw_raw_copy = fw_raw
hash = hashlib.sha1()
while fw_raw_copy:
    #print(hash.hexdigest())
    hash.update(fw_raw_copy[:64])
    if len(fw_raw_copy) < 64:
        fw_raw_copy = b""
    fw_raw_copy = fw_raw_copy[64:]
print(hash.hexdigest())