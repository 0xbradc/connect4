"""
/** @file main.py
 * 
 * @brief Client in Python
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */ 
"""

import socket

class SocketInformation:
    def __init__(self, ip_address, port_num):
        self.ip_address = ip_address
        self.port_num = port_num

def main():
    server_info = SocketInformation("127.0.0.1", 4444)

    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        # Connect to server
        sock.connect((server_info.ip_address, server_info.port_num))
        print(f"Connected to the server on port {server_info.port_num} from IP {server_info.ip_address}")

        while True:
            # Get input from the user
            input_data = input("Enter your move (column number): ")

            # Send the data to the server
            sock.sendall(input_data.encode('utf-8'))

            # Receive the response from the server
            buffer = sock.recv(1024)
            print(f"Server says: {buffer.decode('utf-8')}")

if __name__ == "__main__":
    main()

"""end of file"""
