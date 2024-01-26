/** @file main.rs
 *
 * @brief Client in Rust
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */
use std::io::{self, Read, Write};
use std::net::TcpStream;
use std::str;

struct SocketInformation {
    ip_address: String,
    port_num: u32,
}

fn main() -> io::Result<()> {
    let server_info = SocketInformation {
        ip_address: "127.0.0.1".to_string(),
        port_num: 4444,
    };

    let mut stream = TcpStream::connect(
        server_info.ip_address.clone() + ":" + &server_info.port_num.to_string(),
    )?;
    println!(
        "Connected to the server on port {} from IP {}",
        server_info.port_num,
        server_info.ip_address.clone()
    );

    let mut input = String::new();
    loop {
        println!("Enter your move (column number):");
        io::stdin().read_line(&mut input)?;

        // Send the move to the server
        stream.write_all(input.trim().as_bytes())?;

        // Read server's response
        let mut buffer = [0; 1024];
        let size = stream.read(&mut buffer)?;
        println!(
            "Server says: {}",
            str::from_utf8(&buffer[..size]).unwrap_or("Invalid UTF-8")
        );

        input.clear(); // Clear input for the next move
    }
}

/*** end of file ***/
