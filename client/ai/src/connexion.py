'''Connexion for the server'''
import socket
import sys


P_HELP = "is the port number"
N_HELP = "is the name of the team"
H_HELP = "is the name of the machine; localhost by default"

if len(sys.argv) < 2:
    sys.exit(84)

if len(sys.argv) > 7:
    sys.exit(84)

if sys.argv[1] == "-help":
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("DESCRIPTION:")
    print(f"    -p port     {P_HELP}")
    print(f"    -n name     {N_HELP}")
    print(f"    -h machine  {H_HELP}")
    sys.exit(0)

def get_port():
    '''get the port number'''
    if "-p" in sys.argv:
        index = sys.argv.index("-p")
        if len(sys.argv) > index + 1:
            return sys.argv[index + 1]
    return None

def get_name():
    '''get the name of the team'''
    if "-n" in sys.argv:
        index = sys.argv.index("-n")
        if len(sys.argv) > index + 1:
            return sys.argv[index + 1]
    return None

def get_machine():
    '''get the name of the machine'''
    print(sys.argv)
    if "-h" in sys.argv:
        index = sys.argv.index("-h")
        if len(sys.argv) > index + 1:
            return sys.argv[index + 1]
    return 'localhost'

def main():
    '''Main function to handle client connection and communication.'''
    info = [get_port(), get_name(), get_machine()]
    client_socket = socket.socket()
    try:
        client_socket.connect((info[2], int(info[0])))
        print(f"Connected to {info[2]} on port {info[0]}")
        client_socket.sendall("".encode())
        while True:
            message = input("Commande: ") + "\n"
            client_socket.sendall(message.encode())
            data = client_socket.recv(1024).decode()
            print(data)
            if data.strip() == "dead":
                print("Client dead, On ferme en plus tu pu...")
                break
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()
        print("Connection closed.")



    # client_socket.send("oui\n".encode())
    # data = client_socket.recv(1024).decode()
    # print(data)
    # client_socket.send("oui\n".encode())
    # data = client_socket.recv(1024).decode()
    # print(data)
    # message = input()

    # while message.lower().strip() != 'END\n':
    #     client_socket.send(message.encode())
    #     data = client_socket.recv(1024).decode()
    #     print('Received from server: ' + data)
    #     message = input()

if __name__ == "__main__":
    main()
