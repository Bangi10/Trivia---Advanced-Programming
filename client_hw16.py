import socket
from enum import Enum
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

REQUESTS = {"LOGIN":200, "SIGNUP":201, "LOGOUT":202}
RESPONSES = {"ERRORS": {"REQUEST_ISNT_RELEVANT":50},
             "LOGOUT": {"SUCCESS":90},
             "LOGIN":{
                      "SUCCESS":100,
                      "NAME_NOT_EXISTS":101,
                      "PASSWORD_MISMATCH":102,
                      "USER_ALREADY_LOGINED":103
                      },
             "SIGNUP":{
                      "SUCCESS":110,
                      "NAME_ALREADY_EXISTS":111
                      }
            }

MSG_CODE_LEN = 1
JSON_LENGTH_LEN = 4

def main():
    #try:
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
            try:
                sock.sendall(client_msg)
            except Exception as e:
                print(e)
                exit()
            print(f"Client: {client_msg}")

            # getting a msg from server
            try:
                response_content_str, response_code = receive_response_from_socket(sock)
            except Exception as e:
                print(e)
                exit()
            response_parameters = deserialize_response(response_content_str)
            print(f"Server (after interpret): \n"
                  f"\tcode: {get_code_name(response_code)}\n"
                  f"\tmessage json: {response_parameters}")


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
    response_code = int.from_bytes(sock.recv(MSG_CODE_LEN), "big")
    response_content_len = int.from_bytes(sock.recv(JSON_LENGTH_LEN), "big")
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
        request_parameters["email"] = input("Mail: ")
        return request_parameters, REQUESTS["SIGNUP"]

    return request_parameters, REQUESTS["LOGIN"]


def serialize_request(request_parameters: dict, code: int):
    request = b""
    request_content = json.dumps(request_parameters)

    request += code.to_bytes(1, "big")
    request += len(request_content).to_bytes(4, "big")
    request += request_content.encode()

    return request




if __name__ ==  "__main__":
    main()
