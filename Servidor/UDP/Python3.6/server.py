import socket
import udp_server
from datetime import datetime

class UDPServerMultiClient(udp_server.UDPServer):
    ''' A simple UDP Server for handling multiple clients '''

    def __init__(self, host, port):
        super().__init__(host, port)

    def wait_for_client(self):
        ''' Wait for clients and handle their requests '''

        try:
            while True: # keep alive
                try:
                    # receive request from client
                    data, client_address = self.sock.recvfrom(1024)

                    # handle request
                    self.handle_request(data, client_address)

                except OSError as err:
                    self.printwt(err)

        except KeyboardInterrupt:
            self.shutdown_server()

def main():
    ''' Create a UDP Server and handle multiple clients simultaneously '''

    udp_server_multi_client = UDPServerMultiClient("::", 5678)
    udp_server_multi_client.configure_server()
    udp_server_multi_client.wait_for_client()

if __name__ == '__main__':
    main()
