import socket
import json
# codes
CODE_LOGINRESPONSE = 51
CODE_SIGNUPRESPONSE = 52

def stringifyByFormat(code, obj):
    str_data = json.dumps(obj)
    return chr(code) + len(str_data).to_bytes(4, byteorder = 'little').decode() + str_data


def main():
    # Test server - 1.0.1 (1)
    s = socket.socket()
    host = socket.gethostname()
    port = 25634
    s.connect((host, port))

    data = {
        # "email": "1234@gmail.com",
        "password": "12345678",
        "username": "Artemix"
    }
    str_data = stringifyByFormat(CODE_LOGINRESPONSE, data)
    
    s.send(str_data.encode())
    res = s.recv(1024).decode()

    print('\nResponse:', res)
    s.close()


if __name__ == '__main__':
    main()