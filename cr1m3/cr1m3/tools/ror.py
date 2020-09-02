import sys

def ROR(x, n, bits = 32):
    mask = (2L**n) - 1
    mask_bits = long(x) & mask
    return (x >> n) | (mask_bits << (bits - n))

def ROL(x, n, bits = 32):
    return ROR(x, bits - n)



print 'Lala %x' % (ROR("MessageBoxA", 0x1d))



