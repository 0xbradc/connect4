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

FAMILY = socket.AF_INET
TYPE = None
IP_ADDRESS = ""
PORT = 0
NETWORK_INTERFACE = "eth0"
RESPONSE = b"Copy that!"
MAX_RECEIVING_SIZE = 2048
MY_SERVER_SOCKET = None


def ask_server_type():
    global FAMILY, TYPE, IP_ADDRESS, PORT, MAX_RECEIVING_SIZE
    user_input = input(
        "Enter one of the following options... \n\t[0] TCP IPv4 \n\t[1] UDP \n\t[2] Raw Socket\n"
    )

    if user_input == "0":
        FAMILY = socket.AF_INET
        TYPE = socket.SOCK_STREAM
        PORT = 8081

    elif user_input == "1":
        FAMILY = socket.AF_INET
        TYPE = socket.SOCK_DGRAM
        PORT = 10000

    elif user_input == "2":
        FAMILY = socket.AF_INET
        TYPE = socket.SOCK_RAW
        PORT = 8081
        MAX_RECEIVING_SIZE = 2**16 # Ethernet frame payload limit (2^16 == 65536)

    else:
        print("Invalid choice. Proceeding with default [0]...")
        FAMILY = socket.AF_INET
        TYPE = socket.SOCK_STREAM
        PORT = 8081
    
    print("Server ready!")
    


def run_server():
    global MY_SERVER_SOCKET
    if TYPE == socket.SOCK_STREAM:
        MY_SERVER_SOCKET = socket.socket(family=FAMILY, type=TYPE)  # Creates the socket
        MY_SERVER_SOCKET.bind((IP_ADDRESS, PORT))
        MY_SERVER_SOCKET.listen(
            1
        )  # Listen for incoming connections (parameter is the maximum number of queued connections)
        client_socket, client_addr = MY_SERVER_SOCKET.accept()
        while 1:
            data = client_socket.recvfrom(MAX_RECEIVING_SIZE)
            if not data:
                break
            print(f'Received message: "{data[0].decode()}"')
            client_socket.send(RESPONSE)  # Optional response message

    elif TYPE == socket.SOCK_DGRAM:
        MY_SERVER_SOCKET = socket.socket(family=FAMILY, type=TYPE)  # Creates the socket
        MY_SERVER_SOCKET.bind(("", PORT))  # Binds the server to a specific port
        while 1:
            data, addr = MY_SERVER_SOCKET.recvfrom(
                MAX_RECEIVING_SIZE
            )  # Waits for a message
            if not data:
                break
            print(f'Received message: "{data.decode()}"')
            MY_SERVER_SOCKET.sendto(RESPONSE, addr)  # Optional response message

    elif TYPE == socket.SOCK_RAW:
        MY_SERVER_SOCKET = socket.socket(family=FAMILY, type=TYPE, proto=socket.IPPROTO_RAW)  # Creates the socket
        MY_SERVER_SOCKET.bind((NETWORK_INTERFACE, PORT))
        while 1:
            # Receive data (this is a blocking call)
            data = MY_SERVER_SOCKET.recv(MAX_RECEIVING_SIZE)
            print(f'Received message: "{data.hex()}"')

    else:
        print("Not yet implemented")
        pass


def close_server():
    global MY_SERVER_SOCKET
    MY_SERVER_SOCKET.close()


if __name__ == "__main__":
    ask_server_type()
    run_server()
    close_server()

"""end of file"""
