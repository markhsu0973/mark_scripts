#!/usr/bin/python
def write(filename,keywords,wanna_to_add):
    o = open(filename, "r+")
    ostr = o.read()
    filter = keywords
    position = ostr.find(filter)
    print(position)
    shift = len(filter)
    print(shift)
    o.seek(position + shift)
    o.write("                                                                ")
    o.seek(position + shift)
    wanna_to_add ='"'+ wanna_to_add+'"'
    o.write(wanna_to_add)
    o.close()

write("1.txt", "email:", "mark")