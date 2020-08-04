#Shitty port scanner I found in a tutorial : https://www.youtube.com/watch?v=3Kq1MIfTWCE

import sys
import socket
from datetime import datetime

#Check if argv[1] is an address and assign target to it.
if len(sys.argv) == 2:
	target = socket.gethostbyname(sys.argv[1])
else:
	print("Invalid number of arguments. Syntax : rbps.py [target address]")
	sys.exit()

#Cool banner.
print("-"*50)
print("Scanning target " + target)
print("Started at " + str(datetime.now()))
print("-"*50)

min_port = 50
max_port = 85
open_port_array = []

sys.stdout.write("Checking port 00")
for port in range(min_port, max_port):
	try:
		sys.stdout.write("\b\b"+str(port))
		sys.stdout.flush()
		socket.setdefaulttimeout(0.5)
		error_indicator = socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect_ex((target, port)) #Returns the error indicator. 0 when the connection is successful.
		if error_indicator == 0:
			open_port_array.append(port)
		socket.socket(socket.AF_INET, socket.SOCK_STREAM).close()

	except KeyboardInterrupt:
		print("\nInterrupted by user.")
		sys.exit()

	except socket.gaierror:
		print("Hostname couldn't be resolved.")
		sys.exit()

	except socket.error:
		print("Couldn't connect to server.")
		sys.exit()

sys.stdout.write("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b")
print("Scan done. Open ports : " + str(open_port_array))