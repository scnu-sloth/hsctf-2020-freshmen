def patch(start,end,key):
    n=0
    while(start+n!=end+1):
        addr=start+n
        PatchByte(addr,Byte(addr)^key)
        n+=1
    print("%d Byte has been changed"%n)
    
patch(0x401448,0x401448+189-1,0x56)