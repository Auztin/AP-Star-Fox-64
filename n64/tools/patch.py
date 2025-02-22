import sys, hashlib, bsdiff4

md5 = hashlib.md5()
with open(sys.argv[2], "rb") as f:
  while True:
    data = f.read(1*1024*1024)
    if not data:
      break
    md5.update(data)
print("Patched ROM md5: "+md5.hexdigest())
bsdiff4.file_diff(sys.argv[1], sys.argv[2], sys.argv[3])
