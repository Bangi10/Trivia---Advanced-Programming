import socket
SERVER_IP = "127.0.0.1"
SERVER_PORT = 18820
WANTED_MSG = "Hello"

def main():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connecting to remote computer 92
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)
    #getting a msg from server
    server_msg = sock.recv(5)
    server_msg = server_msg.decode()
    print(server_msg)
    if(server_msg == WANTED_MSG):
        #sending a msg to the server
        sock.sendall(WANTED_MSG)
    try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_address = (SERVER_IP, SERVER_PORT)
            sock.connect(server_address)
            sock.sendall(msg.encode())
            server_msg = sock.recv(1024)
            server_msg = server_msg.decode()
    except Exception as e:
            print("Error: ", e)

if __name__ ==  "__main__":
    main()
