'''Connexion for the server'''
import socket
import sys


P_HELP = "is the port number"
N_HELP = "is the name of the team"
H_HELP = "is the name of the machine; localhost by default"

if len(sys.argv) < 2:
    sys.exit(84)

def main():
    '''main function'''
    print("test main")
    # client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # client.connect(())

main()
