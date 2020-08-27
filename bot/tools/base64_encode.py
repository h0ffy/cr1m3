import base64
import sys

if len(sys.argv) != 2:
	print sys.argv[0] + " <string>"
	sys.exit(0)


encoded = base64.b64encode(str(sys.argv[1]))

print "Decoded (" + str(len(sys.argv[1])) + " bytes): " + str(sys.argv[1])
print "Encoded (" + str(len(encoded)) + " bytes): " + encoded
sys.exit(0)

