import socket
import os
from datetime import datetime

class UDPServer:
    ''' A simple UDP Server '''

    def __init__(self, host, port):
        self.host = host    # Host address
        self.port = port    # Host port
        self.sock = None    # Socket

    def printwt(self, msg):
        ''' Print message with current date and time '''

        current_date_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        print(current_date_time+" "+msg)

    def configure_server(self):
        ''' Configure the server '''

        # create UDP socket with IPv4 addressing
        self.printwt('Creating socket...')
        self.sock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
        self.printwt('Socket created')

        # bind server to the address
        self.printwt("Binding server to "+str(self.host)+":"+str(self.port))
        self.sock.bind((self.host, self.port))
        self.printwt("Server binded to "+str(self.host)+":"+str(self.port))

    def handle_request(self, data, client_address):
        ''' Handle the client '''

        #self.printwt(data)
        print("tiempo",datetime.now().strftime('%Y-%m-%d %H:%M:%S'),"Data recibida:", data, "de:", client_address)

    def wait_for_client(self):
        ''' Wait for a client '''

        try:
            # receive message from a client
            data, client_address = self.sock.recvfrom(1024)

            # handle client's request
            self.handle_request(data, client_address)

        except OSError as err:
            self.printwt(err)

    def shutdown_server(self):
        ''' Shutdown the UDP server '''

        self.printwt('Shutting down server...')
        self.sock.close()

def main():
    ''' Create a UDP Server and respond to a client's resquest '''

    udp_server = UDPServer("::", 5678)
    udp_server.configure_server()
    udp_server.wait_for_client()
    udp_server.shutdown_server()

if __name__ == '__main__':
    main()
