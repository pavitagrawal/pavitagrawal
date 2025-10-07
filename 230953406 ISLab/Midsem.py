import base64
import hashlib
import json
import time
from datetime import datetime
from typing import List
import random
from Crypto.Util.number import getPrime, inverse, long_to_bytes, bytes_to_long

# Rabin key generation

def generate_rabin_keypair(bits=512):
    # p and q primes ≡ 3 mod 4
    while True:
        p = getPrime(bits)
        if p % 4 == 3:
            break
    while True:
        q = getPrime(bits)
        if q % 4 == 3 and q != p:
            break
    n = p * q
    return (p, q, n)

# Rabin encryption: c = m^2 mod n
def rabin_encrypt(m_int, n):
    if m_int >= n:
        raise ValueError("Message integer too large for modulus")
    return pow(m_int, 2, n)

# Rabin decryption returns 4 roots, need to choose correct one
def rabin_decrypt(c, p, q):
    n = p * q
    # Compute mp and mq (roots mod p and q)
    mp = pow(c, (p + 1) // 4, p)
    mq = pow(c, (q + 1) // 4, q)

    # Use CRT to get 4 roots
    yp = inverse(p, q)
    yq = inverse(q, p)

    r1 = (mp * q * yq + mq * p * yp) % n
    r2 = n - r1
    r3 = (mp * q * yq - mq * p * yp) % n
    r4 = n - r3

    return [r1, r2, r3, r4]

def now_timestamp_str():
    return datetime.now().isoformat(sep=' ', timespec='seconds')

def sha512_hex(data: bytes):
    import hashlib
    h = hashlib.sha512()
    h.update(data)
    return h.hexdigest()

# ElGamal key generation and encrypt/decrypt as before (for encrypting Rabin private key maybe)

def generate_elgamal_keypair(bits: int = 512):
    p = getPrime(bits)
    g = random.randint(2, p - 1)
    x = random.randint(1, p - 2)  # private key
    h = pow(g, x, p)  # public key component
    return (p, g, h), x

def elgamal_encrypt_bytes(message_bytes: bytes, pub_key):
    p, g, h = pub_key
    m = int.from_bytes(message_bytes, 'big')
    if m >= p:
        raise ValueError("Message too large for key size")
    k = random.randint(1, p - 2)
    c1 = pow(g, k, p)
    c2 = (m * pow(h, k, p)) % p
    return c1, c2

def elgamal_decrypt_bytes(ciphertext_tuple, priv_key, pub_key):
    c1, c2 = ciphertext_tuple
    p, g, h = pub_key
    x = priv_key
    s = pow(c1, x, p)
    s_inv = pow(s, p - 2, p)  # modular inverse
    m = (c2 * s_inv) % p
    # Convert int back to bytes
    byte_length = (m.bit_length() + 7) // 8
    return m.to_bytes(byte_length, 'big')

# Data storage classes

class customerRecord:
    def __init__(self, timestamp, rabin_encrypted_data_hex, elgamal_encrypted_key_c1_hex, elgamal_encrypted_key_c2_hex,
                 sha512_hash_hex, data_fields_preview=None):
        self.timestamp = timestamp
        self.rabin_encrypted_data_hex = rabin_encrypted_data_hex
        self.elgamal_encrypted_key_c1_hex = elgamal_encrypted_key_c1_hex
        self.elgamal_encrypted_key_c2_hex = elgamal_encrypted_key_c2_hex
        self.sha512_hash_hex = sha512_hash_hex
        self.data_fields_preview = data_fields_preview

class MerchantVerification:
    def __init__(self, timestamp, customer_index, verified_name_hash_hex, verification_note):
        self.timestamp = timestamp
        self.customer_index = customer_index
        self.verified_name_hash_hex = verified_name_hash_hex
        self.verification_note = verification_note


# Generate Rabin keypair for encrypting customer data
rabin_p, rabin_q, rabin_n = generate_rabin_keypair(512)

# Generate ElGamal keypair for encrypting Rabin private key (just for demo)
elgamal_PUB, elgamal_PRIV = generate_elgamal_keypair(1024)

customer_records: List[customerRecord] = []
merchant_verifications: List[MerchantVerification] = []

def customer_module_demo(interactive=True):
    print("\n--- customer Module (Rabin encryption) ---")
    if interactive:
        name = input("Enter customer name: ")
        amount = input("Enter customer amount to send: ")
        card_no = input("Enter customer card number: ")
    else:
        name = "Test User"
        amount = "100"
        card_no = "1234-5678-9012-3456"

    customer_data = {
        "name": name,
        "amount": amount,
        "card_no": card_no
    }
    plaintext_bytes = json.dumps(customer_data, ensure_ascii=False).encode('utf-8')

    # Prepend a fixed prefix to identify the correct root on decrypt (must be shorter than modulus n)
    prefix = b'__RABIN__'  # 8 bytes prefix
    message_with_prefix = prefix + plaintext_bytes
    m_int = bytes_to_long(message_with_prefix)

    if m_int >= rabin_n:
        raise ValueError("Message too long for Rabin modulus, try smaller input.")

    # Encrypt with Rabin
    start_rabin_enc = time.perf_counter()
    c = rabin_encrypt(m_int, rabin_n)
    end_rabin_enc = time.perf_counter()
    rabin_enc_time = end_rabin_enc - start_rabin_enc

    rabin_ciphertext_hex = hex(c)[2:]

    # Encrypt Rabin private key (p, q) with ElGamal to simulate protecting private key

    # For demonstration we just encrypt p concatenated with q as bytes (not realistic, just demo)
    privkey_bytes = rabin_p.to_bytes((rabin_p.bit_length()+7)//8, 'big') + rabin_q.to_bytes((rabin_q.bit_length()+7)//8, 'big')

    # Because ElGamal modulus < p here, we encrypt in chunks if needed; but for demo, let's just encrypt p only (assuming it's < p)
    try:
        c1, c2 = elgamal_encrypt_bytes(rabin_p.to_bytes((rabin_p.bit_length()+7)//8, 'big'), elgamal_PUB)
    except Exception as e:
        print("ElGamal encryption of Rabin private key failed:", e)
        return

    elgamal_enc_key_c1_hex = hex(c1)[2:]
    elgamal_enc_key_c2_hex = hex(c2)[2:]

    name_hash_hex = sha512_hex(name.encode('utf-8'))

    record = customerRecord(
        timestamp=now_timestamp_str(),
        rabin_encrypted_data_hex=rabin_ciphertext_hex,
        elgamal_encrypted_key_c1_hex=elgamal_enc_key_c1_hex,
        elgamal_encrypted_key_c2_hex=elgamal_enc_key_c2_hex,
        sha512_hash_hex=name_hash_hex,
        data_fields_preview={"name": name, "amount": amount}
    )
    customer_records.append(record)

    print("\nCustomer data encrypted with Rabin cryptosystem.")
    print("Rabin ciphertext (hex):", rabin_ciphertext_hex)
    print("ElGamal encrypted Rabin private key part (hex): c1 =", elgamal_enc_key_c1_hex)
    print("ElGamal encrypted Rabin private key part (hex): c2 =", elgamal_enc_key_c2_hex)
    print("SHA-512 hash of customer name (hex):", name_hash_hex)
    print(f"Rabin encryption time: {rabin_enc_time:.6f} seconds")

def merchant_module_demo(record_index=None):
    print("\n--- Merchant Module (Rabin decryption) ---")
    if not customer_records:
        print("No customer records available.")
        return

    if record_index is None:
        print(f"There are {len(customer_records)} customer record(s). Index range: 0 .. {len(customer_records) - 1}")
        try:
            idx_input = input("Enter customer record index to retrieve (default 0): ").strip()
            record_index = int(idx_input) if idx_input != "" else 0
        except Exception:
            record_index = 0

    if record_index < 0 or record_index >= len(customer_records):
        print("Invalid index.")
        return

    record = customer_records[record_index]
    print(f"\nFetching customerRecord at index {record_index}:")
    print(json.dumps(record.__dict__, indent=2))

    # Decrypt Rabin private key part with ElGamal (simulate retrieving private key)
    c1 = int(record.elgamal_encrypted_key_c1_hex, 16)
    c2 = int(record.elgamal_encrypted_key_c2_hex, 16)
    elgamal_encrypted_key = (c1, c2)

    start_elgamal_dec = time.perf_counter()
    decrypted_privkey_bytes = elgamal_decrypt_bytes(elgamal_encrypted_key, elgamal_PRIV, elgamal_PUB)
    end_elgamal_dec = time.perf_counter()
    elgamal_dec_time = end_elgamal_dec - start_elgamal_dec

    # Convert decrypted bytes back to integer p
    p_candidate = int.from_bytes(decrypted_privkey_bytes, 'big')
    print(f"ElGamal decrypted Rabin p (int): {p_candidate}")
    print(f"ElGamal decryption time: {elgamal_dec_time:.6f} seconds")

    # Use stored Rabin q and n as originally generated (in real system you'd store securely)
    # For demo, we will assume merchant knows q and n for decrypting Rabin ciphertext
    # In reality, merchant should get q securely as well (here hardcoded)
    q = rabin_q
    n = rabin_n
    c = int(record.rabin_encrypted_data_hex, 16)

    # Rabin decrypt ciphertext c to get 4 roots
    roots = rabin_decrypt(c, p_candidate, q)
    print(f"Rabin decryption yielded 4 candidate roots (ints):")
    for i, root in enumerate(roots):
        print(f"Root {i+1}: {root}")

    # Try to identify correct root by checking prefix bytes
    prefix = b'__RABIN__'
    correct_plaintext = None
    for r in roots:
        plaintext_bytes = long_to_bytes(r)
        if plaintext_bytes.startswith(prefix):
            correct_plaintext = plaintext_bytes[len(prefix):]  # remove prefix
            break

    if correct_plaintext is None:
        print("Failed to identify correct plaintext root.")
        return

    print("\nDecrypted plaintext JSON string:")
    print(correct_plaintext.decode('utf-8', errors='ignore'))

    # Verify SHA-512 hash of customer name matches stored hash
    try:
        customer_data = json.loads(correct_plaintext.decode('utf-8'))
    except Exception as e:
        print("JSON decode error:", e)
        return

    customer_name = customer_data.get("name", "")
    computed_hash = sha512_hex(customer_name.encode('utf-8'))
    if computed_hash == record.sha512_hash_hex:
        print("SHA-512 hash verification: SUCCESS")
        verification_note = "Hash matched"
    else:
        print("SHA-512 hash verification: FAILED")
        verification_note = "Hash mismatch"

    # Store merchant verification record
    verification = MerchantVerification(
        timestamp=now_timestamp_str(),
        customer_index=record_index,
        verified_name_hash_hex=computed_hash,
        verification_note=verification_note
    )
    merchant_verifications.append(verification)
    print(f"Merchant verification record saved at timestamp {verification.timestamp}")

# Example interactive usage:

if __name__ == "__main__":
    customer_module_demo()
    merchant_module_demo()