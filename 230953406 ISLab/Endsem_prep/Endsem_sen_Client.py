# Implement a secure end-to-end voting system using a client-server architecture that demonstrates:

# Client-Side (Voter):
# Each voter enters a binary vote (0 or 1).
# The vote is hashed using SHA-256.
# The hashed vote is encrypted using ElGamal encryption (which supports homomorphic XOR).
# The encrypted vote is digitally signed using the voter’s RSA private key.
# The client sends both the encrypted vote and digital signature to the server.

# Server-Side (Voting Authority):
# The server receives the encrypted vote and digital signature.
# It verifies the signature using the RSA public key.
# If the signature is valid, it uses ElGamal’s homomorphic XOR property to tally all votes securely.
# Finally, the server sends the decrypted tally result back to the client.

# The implementation must use:
# SHA-256 for hashing
# ElGamal for homomorphic encryption
# RSA for digital signatures
# Socket programming for communication between client and server
# Include proper serialization (JSON) for transmitting encrypted data and signatures.

import socket
import hashlib
import json
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.Util.number import getPrime, inverse, bytes_to_long, long_to_bytes
import random

# ========================= ElGamal Setup ============================= #

def elgamal_keygen(bits=256):
    p = getPrime(bits)
    g = random.randint(2, p - 2)
    x = random.randint(1, p - 2)
    y = pow(g, x, p)
    return (p, g, y), x

def elgamal_encrypt(public_key, m):
    p, g, y = public_key
    k = random.randint(1, p - 2)
    c1 = pow(g, k, p)
    s = pow(y, k, p)
    c2 = (m * s) % p
    return (c1, c2)

def elgamal_decrypt(private_key, public_key, ciphertext):
    p, g, y = public_key
    c1, c2 = ciphertext
    s = pow(c1, private_key, p)
    s_inv = inverse(s, p)
    m = (c2 * s_inv) % p
    return m

# ========================= RSA Setup ============================= #

def rsa_keygen():
    key = RSA.generate(2048)
    return key.publickey(), key

def rsa_sign(private_key, data_bytes):
    h = SHA256.new(data_bytes)
    return pkcs1_15.new(private_key).sign(h)

def rsa_verify(public_key, data_bytes, signature):
    h = SHA256.new(data_bytes)
    try:
        pkcs1_15.new(public_key).verify(h, signature)
        return True
    except (ValueError, TypeError):
        return False

# ========================= Hash Function ============================= #

def compute_hash(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

# ========================= Client Logic ============================= #

def start_client(server_host="127.0.0.1", server_port=65432):
    public_key, private_key = elgamal_keygen()
    rsa_public_key, rsa_private_key = rsa_keygen()

    print("\n--- CLIENT STARTED ---")
    print("ElGamal Public Key:", public_key)
    print("ElGamal Private Key:", private_key)

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_host, server_port))

    votes = [
        {"name": "A", "contestor": "BA", "vote": 1},
        {"name": "B", "contestor": "BA", "vote": 0},
        {"name": "C", "contestor": "BA", "vote": 1},
        {"name": "D", "contestor": "BB", "vote": 1}
    ]

    for v in votes:
        vote_hash = compute_hash(str(v["vote"]).encode())
        vote_hash_int = bytes_to_long(vote_hash.encode())

        c1, c2 = elgamal_encrypt(public_key, vote_hash_int)

        c1_bytes = str(c1).encode()
        c2_bytes = str(c2).encode()

        sig_c1 = rsa_sign(rsa_private_key, c1_bytes)
        sig_c2 = rsa_sign(rsa_private_key, c2_bytes)

        v["c1"] = c1
        v["c2"] = c2
        v["signature_c1"] = sig_c1.hex()
        v["signature_c2"] = sig_c2.hex()

    message = {
        "elgamal_public_key": public_key,
        "elgamal_private_key": private_key,
        "votes": votes
    }

    client_socket.send(json.dumps(message).encode())
    print("\n[CLIENT] Votes sent to server.")

    tally = client_socket.recv(8192).decode()
    print("\n[CLIENT] Final tally from server:", tally)

    client_socket.close()

if __name__ == "__main__":
    start_client()
