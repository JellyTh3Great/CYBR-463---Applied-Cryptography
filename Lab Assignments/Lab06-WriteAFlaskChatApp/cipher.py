import hashlib
from Crypto.Cipher import AES
from Crypto.Hash import HMAC, SHA256


def get_derived_keys(shared_secret):
    secret_bytes = str(shared_secret).encode('utf-8')
    aes_key = hashlib.sha256(secret_bytes + b":AES").digest()
    hmac_key = hashlib.sha256(secret_bytes + b":HMAC").digest()

    return aes_key, hmac_key
    

def encrypt_message(aes_key, hmac_key, plaintext):
    cipher = AES.new(aes_key, AES.MODE_CTR)
    ciphertext = cipher.encrypt(plaintext)
    message = cipher.nonce + ciphertext
    signed_message = HMAC.new(hmac_key, message, digestmod=SHA256)
    signature = signed_message.digest()
    encrypted_message = signature + cipher.nonce + ciphertext
    return encrypted_message

def decrypt_message(aes_key, hmac_key, packet_data):
    signature, nonce, ciphertext = (packet_data[:32], packet_data[32:40], packet_data[40:])
    message = nonce + ciphertext
    signed_message = HMAC.new(hmac_key, message, digestmod=SHA256)
    if signature == signed_message.digest():
        cipher = AES.new(aes_key, AES.MODE_CTR, nonce=nonce)
        plaintext = cipher.decrypt(ciphertext)
        return plaintext
    else:
        return "Error With Decryption"