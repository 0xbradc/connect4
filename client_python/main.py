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
import struct

FAMILY = socket.AF_INET
TYPE = None
IP_ADDRESS = ""
PORT = 0
NETWORK_INTERFACE = "eth0"
MESSAGE = b"Hello, world!"
MY_CLIENT_SOCKET = None
MAX_RECEIVING_SIZE = 2048


def ask_client_type():
    global TYPE, IP_ADDRESS, PORT
    user_input = input(
        "Enter one of the following options... \n\t[0] TCP IPv4 \n\t[1] UDP \n\t[2] Raw Socket\n"
    )
    if user_input == "0":
        TYPE = socket.SOCK_STREAM
        IP_ADDRESS = "127.0.0.1"
        PORT = 8081
        print("Client Ready!")

    elif user_input == "1":
        TYPE = socket.SOCK_DGRAM
        IP_ADDRESS = "localhost"
        PORT = 10000
        print("Client Ready!")

    elif user_input == "2":
        TYPE = socket.SOCK_RAW
        PORT = 8081
        print("Client Ready!")

    else:
        print("Invalid choice. Proceeding with default [0]...")
        TYPE = socket.SOCK_STREAM


def ask_message():
    global MESSAGE
    temp = input('\nWhat message would you like to send? (input "q" to quit)\n')
    if temp == "q":
        exit()
    MESSAGE = temp.encode("utf-8")  # Convert to binary


def run_client():
    global MY_CLIENT_SOCKET
    if not MY_CLIENT_SOCKET:
        MY_CLIENT_SOCKET = socket.socket(family=FAMILY, type=TYPE)
        MY_CLIENT_SOCKET.connect((IP_ADDRESS, PORT))

    if TYPE == socket.SOCK_RAW:
        # Construct a simple Ethernet frame
        ethernet_frame = struct.pack('!6s6sH', b'\xff\xff\xff\xff\xff\xff', b'\x00\x11\x22\x33\x44\x55', 0x0800)
        # Send the raw Ethernet frame
        MY_CLIENT_SOCKET.sendto(ethernet_frame, (NETWORK_INTERFACE, PORT))

    else:
        MY_CLIENT_SOCKET.send(MESSAGE)  # Send message
        data, addr = MY_CLIENT_SOCKET.recvfrom(
            MAX_RECEIVING_SIZE
        )  # Wait for response where data is returned data and addr is the remote address
        print(data.decode(), addr)


def close_client():
    MY_CLIENT_SOCKET.close()


if __name__ == "__main__":
    ask_client_type()

    while 1:
        try:
            ask_message()
            run_client()
        except KeyboardInterrupt:
            break
        except Exception as e:
            print(f"An unexpected error occurred: {e}")

    close_client()

"""end of file"""
