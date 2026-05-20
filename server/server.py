import socket

HOST = "0.0.0.0"
PORT = 5001

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"Listening on port {PORT}...")
    conn, addr = s.accept()
    with conn:
        print(f"Connected from {addr}")
        data = conn.recv(1024)
        print(f"Received: {data.decode().strip()}")