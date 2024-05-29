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
    '''main function'''
    info = [get_port(), get_name(), get_machine()]
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((info[2], int(info[0])))
    print(client.recv(4096).decode())


main()