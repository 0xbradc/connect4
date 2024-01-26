/** @file main.go
 *
 * @brief Client in Go
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */

package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

type SocketInformation struct {
	IPAddress string
	PortNum   int
}

func main() {
	serverInfo := SocketInformation{
		IPAddress: "127.0.0.1",
		PortNum:   4444,
	}

	// Connect to the server
	connectionString := fmt.Sprintf("%s:%d", serverInfo.IPAddress, serverInfo.PortNum)
	conn, err := net.Dial("tcp", connectionString)
	if err != nil {
		fmt.Println("Error connecting:", err)
		os.Exit(1)
	}
	defer conn.Close()

	fmt.Printf("Connected to the server on port %d from IP %s\n", serverInfo.PortNum, serverInfo.IPAddress)

	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("Enter your move (column number):")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)

		// Send the move to the server
		_, err = conn.Write([]byte(input))
		if err != nil {
			fmt.Println("Error sending data:", err)
			break
		}

		// Read server's response
		buffer := make([]byte, 1024)
		size, err := conn.Read(buffer)
		if err != nil {
			fmt.Println("Error reading response:", err)
			break
		}
		fmt.Printf("Server says: %s\n", string(buffer[:size]))
	}
}

/*** end of file ***/
