import socket
import enum
SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
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
        server_msg = sock.recv(5).decode()
        print(f"Server: {server_msg}")

        # sending a msg to the server
        request_parameters, code = get_request_parameters()
        client_msg = create_encoded_request(request_parameters, code)
        sock.sendall(client_msg)
        print(f"Client: {client_msg}")

        # getting a msg from server
        server_msg = sock.recv(1024).decode()
        print(f"Server: {server_msg}")
    except Exception as e:
            print("Error: ", e)

def get_request_parameters():
    login_or_signup = input("l for login, anything else for signup: ")
    request_parameters = dict()
    request_parameters["username"] = input("Username: ")
    request_parameters["password"] = input("Password: ")

    if login_or_signup != "l":
        request_parameters["mail"] = input("Mail: ")
        return request_parameters, REQUESTS.SIGNUP.value

    return request_parameters, REQUESTS.LOGIN.value


def create_encoded_request(request_parameters: dict, code: int):
    request = b""
    request_content = str(request_parameters)

    request += code.to_bytes(1, "big")
    request += len(request_content).to_bytes(4, "big")
    request += request_content.encode()

    return request




if __name__ ==  "__main__":
    main()
