# executing on python 2.7
import socket

connect_ip = '127.0.0.1'
connect_port = 666
def handleConnect(conn):
    conn.sendall(bytes('GET / HTTP/1.0\r\n\r\n\0\r\n\r\n'))
    server_rply = conn.recv(1024)
    print str(server_rply)

# under are the simple client functions
ip_port = (connect_ip, connect_port)
conn = socket.socket()
conn.connect(ip_port)
print "----connected on port:", ip_port
handleConnect(conn)
conn.close()
