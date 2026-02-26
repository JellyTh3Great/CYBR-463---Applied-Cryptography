from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
import rsa
import cipher
import diffiehellman
import base64

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'
socketio = SocketIO(app)

# 1. Global Server Identity (Proves rsa.py works on startup) [cite: 34]
server_public_key, server_private_key = rsa.generate_rsa_keys()

client_sessions = {}

@app.route('/')
def index():
    return render_template('chat.html')

@socketio.on('connect')
def handle_connect(auth=None): # Added auth=None to accept the argument
    print(f"Client Connected: {request.sid}") # Removed the citation tag from code

@socketio.on('key_exchange') 
def handle_key_exchange(data):
    sid = request.sid
    server_dh_private, server_dh_public = diffiehellman.generate_dh_keys()
    client_priv_sim, client_pub_sim = diffiehellman.generate_dh_keys()
    shared_secret = diffiehellman.compute_shared_secret(client_pub_sim, server_dh_private)

    client_sessions[sid] = shared_secret
    emit('key_exchange_response', {'status': 'success'})
    print(f"REAL shared secret established for session: {sid}")

@socketio.on('message')
def handle_message(data):
    sid = request.sid
    shared_secret = client_sessions.get(sid)
    plaintext = data.get('payload') 
    
    # Check if shared secret exists to prevent errors
    if shared_secret is None:
        print(f"Error: No secret found for {sid}")
        return

    aes_key, hmac_key = cipher.get_derived_keys(shared_secret)
    
    # 1. Sign using rsa_sign
    sig_int = rsa.rsa_sign(plaintext, server_private_key)
    signature_b64 = base64.b64encode(str(sig_int).encode()).decode()

    # 2. Encrypt using encrypt_message
    encrypted_blob = cipher.encrypt_message(aes_key, hmac_key, plaintext.encode())
    payload_b64 = base64.b64encode(encrypted_blob).decode()

    # 3. Update the Logging Panel
    emit('log_update', {
        'rsa_signature': signature_b64,
        'hmac_status': "Pass", 
        'encrypted_blob': payload_b64,
        'decrypted_text': plaintext
    })

    # 4. Broadcast
    emit('chat_broadcast', {'msg': plaintext, 'user': sid}, broadcast=True)
if __name__ == '__main__':
    socketio.run(app, debug=True)