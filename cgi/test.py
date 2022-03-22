import sys
import os

for line in sys.stdin: print (line)
str = os.environ.get("QUERY_STRING")
print(str)