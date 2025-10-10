import socket
import threading
import time
from flask import Flask, jsonify

# ────────────────────────────────
# ⚙️ 전역 변수
# ────────────────────────────────
esp_conn = None
esp_lock = threading.Lock()

# ────────────────────────────────
# 📡 Flask 앱: ESP 연결 상태 확인
# ────────────────────────────────
status_app = Flask(__name__)

@status_app.route('/esp_status')
def esp_status():
    with esp_lock:
        connected = esp_conn is not None
    return jsonify({'esp_connected': connected})


# ────────────────────────────────
# 🔌 ESP32 소켓 서버 (port 6000)
# ────────────────────────────────
def handle_esp32():
    global esp_conn
    srv = socket.socket()
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(('0.0.0.0', 6000))
    srv.listen(1)
    print('[ESP32] 연결 대기 중 (port 6000)...')

    while True:
        conn, addr = srv.accept()
        print('[ESP32] 연결됨:', addr)
        with esp_lock:
            esp_conn = conn

        try:
            while True:
                data = conn.recv(1024)
                if not data:
                    print('[ESP32] 연결 종료')
                    break
                print('[ESP32 → 서버]:', data.decode().strip())
        except Exception as e:
            print('[ESP32] 오류:', e)
        finally:
            conn.close()
            with esp_lock:
                esp_conn = None
            print('[ESP32] 재연결 대기 중...')


# ────────────────────────────────
# 📱 앱인벤터 소켓 서버 (port 6001)
# ────────────────────────────────
def handle_app_client(conn):
    global esp_conn
    print('[APP] 앱인벤터 연결됨')

    try:
        while True:
            data = conn.recv(1024)
            if not data:
                print('[APP] 연결 종료')
                break

            cmd = data.decode().strip()
            print(f'[APP → 서버] 명령 수신: {cmd}')

            with esp_lock:
                if esp_conn:
                    try:
                        esp_conn.sendall((cmd + '\n').encode())
                        print(f'[서버 → ESP32] 전달: {cmd}')
                        conn.send(b'OK: Sent to ESP\n')
                    except Exception as e:
                        print(f'[ESP32 전송 오류]: {e}')
                        esp_conn = None
                        conn.send(b'ERROR: ESP send failed\n')
                else:
                    conn.send(b'ERROR: ESP not connected\n')
    except Exception as e:
        print('[APP] 오류:', e)
    finally:
        conn.close()


def start_app_server():
    srv = socket.socket()
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(('0.0.0.0', 6001))
    srv.listen(1)
    print('[APP] 앱인벤터 연결 대기 중 (port 6001)...')
    while True:
        conn, _ = srv.accept()
        threading.Thread(target=handle_app_client, args=(conn,), daemon=True).start()


# ────────────────────────────────
# 🧠 메인 실행
# ────────────────────────────────
if __name__ == '__main__':
    # ESP32 소켓 서버 실행
    threading.Thread(target=handle_esp32, daemon=True).start()

    # Flask 상태 확인 서버 실행 (port 6005)
    threading.Thread(target=lambda: status_app.run(host='0.0.0.0', port=6005), daemon=True).start()

    # 앱인벤터 소켓 서버 실행
    start_app_server()
