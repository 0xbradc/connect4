use std::io::{Error, Read, Write};
/** @file main.rs
 *
 * @brief Server in Rust
 *
 * @par   
 * COPYRIGHT NOTICE: MIT License
 */
use std::net::{TcpListener, TcpStream};
use std::thread;

struct SocketInformation {
    ip_address: String,
    port_num: u32,
}

fn handle_client(mut stream: TcpStream) -> Result<(), Error> {
    println!("New connection: {}", stream.peer_addr()?);

    let mut buffer = [0; 512]; // Buffer for incoming data
    while match stream.read(&mut buffer) {
        Ok(size) => {
            // Process Connect 4 game data here
            // For example, deserialize buffer into game state, update it, and serialize back
            stream.write(&buffer[..size])?; // Echo everything received
            true
        }
        Err(_) => {
            println!("An error occurred with: {}", stream.peer_addr()?);
            false
        }
    } {}

    Ok(())
}

fn main() -> Result<(), Error> {
    let server_info = SocketInformation {
        ip_address: "127.0.0.1".to_string(),
        port_num: 4444,
    };

    let listener = TcpListener::bind(
        server_info.ip_address.clone() + ":" + &server_info.port_num.to_string(),
    )?;
    println!(
        "Server listening on port {} from IP {}",
        server_info.port_num,
        server_info.ip_address.clone()
    );

    // Accept connections and process them, spawning a new thread for each one
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                thread::spawn(|| {
                    handle_client(stream).unwrap_or_else(|error| eprintln!("{:?}", error));
                });
            }
            Err(e) => {
                eprintln!("Connection failed: {}", e);
            }
        }
    }

    Ok(())
}

/*** end of file ***/
