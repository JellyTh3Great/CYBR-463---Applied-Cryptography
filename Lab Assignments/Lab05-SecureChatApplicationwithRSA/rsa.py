import secrets
import hashlib
import tkinter

# Task 1: Miller-Rabin primality test
def is_prime(n, k=5):
    if n < 2: return False
    if n == 2 or n == 3: return True
    if n % 2 == 0: return False

    # Find r and d such that n-1 = 2^r * d
    r, d = 0, n - 1
    while d % 2 == 0:
      r += 1
      d //= 2

    for _ in range(k):
      a = secrets.randbelow(n - 4) + 2
      x = pow(a, d, n)
      if x == 1 or x == n - 1:
          continue
      for _ in range(r - 1):
          x = pow(x, 2, n)
          if x == n - 1:
              break
      else:
          return False
    return True


# Task 2: Generate a large random prime of specified bit length
def get_random_prime(bits=1024):

    # Generate random number with MSB and LSB set to ensure bit length and oddity
    while True:
        p = secrets.randbits(bits) | (1 << (bits - 1)) | 1
        if is_prime(p):
            return p

# Task 3: Generate RSA Keypair
def generate_rsa_keys():
    e = 65537
    p = get_random_prime(1024)
    q = get_random_prime(1024)

    n = p * q
    phi = (p - 1) * (q - 1)

    # Compute modular inverse d
    d = pow(e, -1, phi)

    # Return (Public Key (e, n), Private Key (d, n))
    return (e, n), (d, n)

# Task 4: Core RSA primitive
def rsa_process(data_int, key):
    exponent, n = key
    return pow(data_int, exponent, n)

# Task 5: Hash-then-Sign scheme. Hashes message with SHA-256 and signs the result
def rsa_sign(message, private_key):
    h = hashlib.sha256(message.encode()).hexdigest()
    data_int = int(h, 16)
    return rsa_process(data_int, private_key)

# Task 6: Verify the signature
def rsa_verify(message, signature, public_key):
    h = hashlib.sha256(message.encode()).hexdigest()
    data_int = int(h, 16)
    decrypted_hash = rsa_process(signature, public_key)
    return data_int == decrypted_hash
