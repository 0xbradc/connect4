/** @file main.go
 *
 * @brief Server in Go
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */

package main

import (
	"fmt"
	"io"
	"net"
	"os"
	"../common_go/comms.go"
	"../common_go/main.go"
)

func handleClient(conn net.Conn) {
	defer conn.Close()

	fmt.Printf("New connection: %s\n", conn.RemoteAddr().String())

	buffer := make([]byte, 512) // Buffer for incoming data
	for {
		size, err := conn.Read(buffer)
		if err != nil {
			if err != io.EOF {
				fmt.Printf("An error occurred with: %s, %v\n", conn.RemoteAddr().String(), err)
			}
			break
		}

		// Echo everything received
		_, err = conn.Write(buffer[:size])
		if err != nil {
			fmt.Printf("Write error: %v\n", err)
			break
		}
		fmt.Printf("Received: %s\n", string(buffer[:size]))
	}
}

func main() {
	server_info := game.SocketInformation{
		IPAddress: game.DEFAULT_IP_ADDRESS,
		PortNum:   game.DEFAULT_PORT_NUM,
	}

	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", server_info.IPAddress, server_info.PortNum))
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error listening: %v\n", err)
		os.Exit(1)
	}
	defer listener.Close()

	fmt.Printf("Server listening on port %d from IP %s\n", server_info.PortNum, server_info.IPAddress)

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Fprintf(os.Stderr, "Connection failed: %v\n", err)
			continue
		}
		go handleClient(conn)
	}
}

/*** end of file ***/
