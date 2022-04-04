#!/usr/bin/env python3

import cgi
import html

form = cgi.FieldStorage()
text1 = form.getfirst("test", "not set")
text2 = form.getfirst("test2", "not set")
text1 = html.escape(text1)
text2 = html.escape(text2)

print("Content-type: text/html\r\n")
print("First name: ", text1)
print("Second name: ", text2)