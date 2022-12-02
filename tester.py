#!/bin/python
from pwn import *;

#context.log_level = 'debug'

pr = process('./bin/studentList')

for i in range(0, 10):
    print(pr.recvline_contains("6"))
    pr.sendline("1")
    #recvline_contains("Alter")

    # age
    print(pr.recvline())
    pr.sendline(str(i))

    #mnumber
    print(pr.recvline())
    pr.sendline(str(i))

    #bithday
    print(pr.recvline())
    pr.sendline("23.23.2323")

    # name
    print(pr.recvline())
    pr.sendline("Hello" + str(i))

    # surname
    print(pr.recvline())
    pr.sendline("Hellosur" + str(i))
    
    # startdate
    print(pr.recvline())
    pr.sendline("23.23.2323")
    
    #enddate
    print(pr.recvline())
    pr.sendline("23.23.2323")
    pr.send("\n")
    

print(pr.recvline_contains("6"))
pr.sendline("4")
print(pr.recv())
pr.interactive()

while(True):
    try:
        print(str(pr.recvline()))
    except:
        break;


