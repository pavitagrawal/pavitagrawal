import socket
import json
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.Util.number import inverse, long_to_bytes, bytes_to_long

# ------------------- ElGamal Functions ------------------- #
def elgamal_decrypt(private_key, public_key, ciphertext):
    p, g, y = public_key
    c1, c2 = ciphertext
    s = pow(c1, private_key, p)
    s_inv = inverse(s, p)
    m = (c2 * s_inv) % p
    return m

# ------------------- RSA Verification ------------------- #
def rsa_verify(public_key, data_bytes, signature_hex):
    h = SHA256.new(data_bytes)
    signature = bytes.fromhex(signature_hex)
    try:
        pkcs1_15.new(public_key).verify(h, signature)
        return True
    except (ValueError, TypeError):
        return False

# ------------------- Server Logic ------------------- #
def start_server(host="127.0.0.1", port=65432):
    print(f"Server listening on {host}:{port}")
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    while True:
        client_socket, addr = server_socket.accept()
        print(f"\nConnection from {addr}")

        data = client_socket.recv(8192)
        vote_data = json.loads(data.decode())

        public_key = tuple(vote_data["elgamal_public_key"])
        private_key = vote_data["elgamal_private_key"]
        votes = vote_data["votes"]

        # Create new RSA keypair (assuming known public key for verify)
        rsa_key = RSA.generate(2048)
        rsa_public_key = rsa_key.publickey()

        final_tally = {"BA": 0, "BB": 0}

        print("\nName\tContestor\tVoteHash(Int)\tValidSignature")
        for v in votes:
            c1, c2 = int(v["c1"]), int(v["c2"])
            sign_c1 = v["signature_c1"]
            sign_c2 = v["signature_c2"]

            valid = rsa_verify(rsa_public_key, str(c1).encode(), sign_c1) and rsa_verify(rsa_public_key, str(c2).encode(), sign_c2)

            m = elgamal_decrypt(private_key, public_key, (c1, c2))
            print(f"{v['name']}\t{v['contestor']}\t{m}\t{valid}")

            if valid:
                final_tally[v["contestor"]] ^= m  # XOR property of ElGamal

        print("\nFinal Tally:")
        for k, val in final_tally.items():
            print(f"{k}: {val}")

        client_socket.send(json.dumps(final_tally).encode())
        client_socket.close()

if __name__ == "__main__":
    start_server()
