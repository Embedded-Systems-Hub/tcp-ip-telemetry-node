import socket
import json

HOST = "0.0.0.0"
PORT = 5001

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(5)
    print(f"Listening on port {PORT}...")
    while True:
        conn, addr = s.accept()
        with conn:
            data = conn.recv(4096).decode().strip()
            if not data:
                continue
            try:
                msg = json.loads(data)
                print(f"[{addr[0]}] id={msg['machine_id']} state={msg['state']} "
                      f"temp={msg['temp']:.2f} vibration={msg['vibration']:.3f} "
                      f"fault={msg['fault_code']} uptime={msg['uptime']}s")
            except json.JSONDecodeError as e:
                print(f"parse error: {e} | raw: {data}")