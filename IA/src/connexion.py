'''Connexion for the server'''
import socket
import sys


P_HELP = "is the port number"
N_HELP = "is the name of the team"
H_HELP = "is the name of the machine; localhost by default"

if len(sys.argv) < 2:
    sys.exit(84)

if len(sys.argv) > 6:
    sys.exit(84)

if sys.argv[1] == "-help":
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("DESCRIPTION:")
    print(f"    -p port     {P_HELP}")
    print(f"    -n name     {N_HELP}")
    print(f"    -h machine  {H_HELP}")
    sys.exit(0)

def main():
    '''main function'''
    print("test main")
    # client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # client.connect(())

main()
