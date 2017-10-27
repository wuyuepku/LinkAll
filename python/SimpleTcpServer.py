# executing on python 2.7
import socket

listning_port = 666
def handleConnect(conn, addr):
    data = conn.recv(1024)
    print "----receving data, length(including \\0) =", len(data)
    print data
    conn.send(bytes("GET http://60.205.187.189 HTTP/1.0\r\n\r\n"))

# under are the simple server functions
ip_port = ('0.0.0.0', listning_port) # better not use '127.0.0.1' or 'localhost'
web = socket.socket()
web.bind(ip_port)
web.listen(5)
if True: # or while True:
    print "----listening on port:", listning_port
    conn, addr = web.accept()
    print "----received a connect on", addr
    handleConnect(conn, addr)
    conn.close()
web.close()
