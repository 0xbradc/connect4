/** @file comms.go
*
* @brief Communications infrastructure in Go
*
* @par   
* COPYRIGHT NOTICE: MIT License
*/

package comms

const DEFAULT_IP_ADDRESS string = "127.0.0.1";
const DEFAULT_PORT_NUM int = 4444;

type SocketInformation struct {
	IPAddress string
	PortNum   int
}

/*** end of file ***/
