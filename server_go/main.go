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
)

type SocketInformation struct {
	IPAddress string
	PortNum   int
}

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
	serverInfo := SocketInformation{
		IPAddress: "127.0.0.1",
		PortNum:   4444,
	}

	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", serverInfo.IPAddress, serverInfo.PortNum))
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error listening: %v\n", err)
		os.Exit(1)
	}
	defer listener.Close()

	fmt.Printf("Server listening on port %d from IP %s\n", serverInfo.PortNum, serverInfo.IPAddress)

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
