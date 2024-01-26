"""
/** @file main.py
 * 
 * @brief Server in Python
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */ 
"""

import socket
import threading

class SocketInformation:
    def __init__(self, ip_address, port_num):
        self.ip_address = ip_address
        self.port_num = port_num

def handle_client(connection, address):
    print(f"New connection: {address}")

    try:
        while True:
            buffer = connection.recv(512)  # Buffer for incoming data
            if not buffer:
                break

            # Process Connect 4 game data here (if needed)
            # For now, we'll just echo everything received
            connection.sendall(buffer)
            print(f"Received: {buffer.decode('utf-8')}")

    except Exception as e:
        print(f"An error occurred with: {address}, {e}")

    finally:
        connection.close()

def main():
    server_info = SocketInformation("127.0.0.1", 4444)

    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((server_info.ip_address, server_info.port_num))
        server_socket.listen()

        print(f"Server listening on port {server_info.port_num} from IP {server_info.ip_address}")

        # Accept connections and process them, spawning a new thread for each one
        while True:
            client_conn, client_addr = server_socket.accept()
            threading.Thread(target=handle_client, args=(client_conn, client_addr)).start()

if __name__ == "__main__":
    main()

"""end of file"""
