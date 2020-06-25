import socket
import csv
  
UDP_IP = "::" # = 0.0.0.0 u IPv4
UDP_PORT = 5678

sock = socket.socket(socket.AF_INET6,socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print "Data recibida:", data,"de",addr
	archivo = csv.writer(open("datos.csv","ab"))
	archivo.writerow([data,addr])
