import socket
from enum import Enum
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

REQUESTS = {"LOGIN":200, "SIGNUP":201}
RESPONSES = {"LOGIN":{
                      "SUCCESS":100,
                      "USER_NOT_EXISTS":101,
                      "USER_ALREADY_LOGINED":102
                      },
             "SIGNUP":{
                      "SUCCESS":110,
                      "NAME_ALREADY_EXISTS":111
                      }
            }

class PROTOCOL_LENS(Enum):
    MSG_CODE = 1
    CONTENT_LENGTH = 4

def main():
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connecting to remote computer 92
            server_address = (SERVER_IP, SERVER_PORT)
            sock.connect(server_address)

            while True:
                if input("<<< ") != "":
                    break

                # sending a msg to the server
                request_parameters, request_code = input_request_parameters()
                client_msg = serialize_request(request_parameters, request_code)
                sock.sendall(client_msg)
                print(f"Client: {client_msg}")

                # getting a msg from server
                response_content_str, response_code = receive_response_from_socket(sock)
                response_parameters = deserialize_response(response_content_str)
                print(f"Server (after interpret): \n"
                      f"\tcode: {get_code_name(response_code)}\n"
                      f"\tmessage json: {request_parameters}")

    except Exception as e:
            print("Error: ", e)

def get_code_name(code: int):
    for request_tuple in REQUESTS.items():
        if request_tuple[1] == code:
            return f"REQUESTS :: {request_tuple[0]}"
    for response_type_tuple in RESPONSES.items():
        for response_tuple in response_type_tuple[1].items():
            if response_tuple[1] == code:
                return f"RESPONSES :: {response_type_tuple[0]} :: {response_tuple[0]}"
    return "CODE DOESN'T EXIST"


def receive_response_from_socket(sock: socket):
    response_code = int(sock.recv(PROTOCOL_LENS.MSG_CODE.value))
    response_content_len = int(sock.recv(PROTOCOL_LENS.CONTENT_LENGTH.value))
    response_content_str = sock.recv(response_content_len).decode()
    return response_content_str, response_code

def deserialize_response(response_content_str: str):
    return json.loads(response_content_str)

def input_request_parameters():
    login_or_signup = input("l for login, anything else for signup: ")
    request_parameters = dict()
    request_parameters["username"] = input("Username: ")
    request_parameters["password"] = input("Password: ")

    if login_or_signup != "l":
        request_parameters["mail"] = input("Mail: ")
        return request_parameters, REQUESTS.SIGNUP.value

    return request_parameters, REQUESTS.LOGIN.value


def serialize_request(request_parameters: dict, code: int):
    request = b""
    request_content = str(request_parameters)

    request += code.to_bytes(1, "big")
    request += len(request_content).to_bytes(4, "big")
    request += request_content.encode()

    return request




if __name__ ==  "__main__":
    main()
