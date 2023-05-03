import socket
import enum
SERVER_IP = "127.0.0.1"
SERVER_PORT = 18820
WANTED_MSG = "Hello"

class REQUESTS(enum.Enum):
    LOGIN = 100
    SIGNUP = 110

def main():
    try:
        # Create a TCP/IP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connecting to remote computer 92
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)

        # getting a msg from server
        server_msg = sock.recv(5)
        server_msg = server_msg.decode()
        print(server_msg)

        # sending a msg to the server
        if(server_msg == WANTED_MSG):
            sock.sendall(WANTED_MSG.encode())

    except Exception as e:
            print("Error: ", e)

def create_request(pars: dict):
    buffer = []
    buffer.append(bytes)
if __name__ ==  "__main__":
    main()
