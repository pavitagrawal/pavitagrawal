import base64
import hashlib
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256

# ==============================
# 1. Caesar Cipher
# ==============================
def caesar_encrypt(plaintext, shift):
    result = ""
    for char in plaintext:
        if char.isalpha():
            base = 'A' if char.isupper() else 'a'
            result += chr((ord(char) - ord(base) + shift) % 26 + ord(base))
        else:
            result += char
    return result

def caesar_decrypt(ciphertext, shift):
    return caesar_encrypt(ciphertext, -shift)


# ==============================
# 2. AES Symmetric (CBC Mode)
# ==============================
def pad(data):
    return data + (16 - len(data) % 16) * chr(16 - len(data) % 16)

def unpad(data):
    return data[:-ord(data[-1])]

def aes_demo():
    key = get_random_bytes(16)
    iv = get_random_bytes(16)
    cipher = AES.new(key, AES.MODE_CBC, iv)

    plaintext = input("Enter message to encrypt with AES: ")
    padded = pad(plaintext)
    ciphertext = cipher.encrypt(padded.encode())

    print("Ciphertext (b64):", base64.b64encode(ciphertext).decode())

    # decrypt
    cipher_dec = AES.new(key, AES.MODE_CBC, iv)
    decrypted = unpad(cipher_dec.decrypt(ciphertext).decode())
    print("Decrypted:", decrypted)


# ==============================
# 3. RSA Encryption/Decryption
# ==============================
def rsa_demo():
    key = RSA.generate(2048)
    public_key = key.publickey()
    cipher = PKCS1_OAEP.new(public_key)

    msg = input("Enter message to encrypt with RSA: ").encode()
    encrypted = cipher.encrypt(msg)
    print("Encrypted (hex):", encrypted.hex())

    decipher = PKCS1_OAEP.new(key)
    decrypted = decipher.decrypt(encrypted)
    print("Decrypted:", decrypted.decode())


# ==============================
# 4. Hybrid AES + RSA
# ==============================
def hybrid_demo():
    # RSA setup
    rsa_key = RSA.generate(2048)
    public_key = rsa_key.publickey()
    rsa_cipher = PKCS1_OAEP.new(public_key)

    # AES setup
    aes_key = get_random_bytes(16)
    iv = get_random_bytes(16)
    aes_cipher = AES.new(aes_key, AES.MODE_CBC, iv)

    plaintext = input("Enter message for Hybrid Encryption: ")
    padded = pad(plaintext)
    ciphertext = aes_cipher.encrypt(padded.encode())

    enc_aes_key = rsa_cipher.encrypt(aes_key)

    print("Encrypted AES key (hex):", enc_aes_key.hex())
    print("Encrypted data (b64):", base64.b64encode(ciphertext).decode())

    # Decrypt AES key
    rsa_decipher = PKCS1_OAEP.new(rsa_key)
    dec_aes_key = rsa_decipher.decrypt(enc_aes_key)

    aes_dec = AES.new(dec_aes_key, AES.MODE_CBC, iv)
    decrypted = unpad(aes_dec.decrypt(ciphertext).decode())
    print("Decrypted:", decrypted)


# ==============================
# 5. Hashing (SHA-512)
# ==============================
def hash_demo():
    msg = input("Enter message to hash (SHA-512): ").encode()
    h = hashlib.sha512(msg).hexdigest()
    print("SHA-512 Hash:", h)


# ==============================
# 6. Digital Signature
# ==============================
def signature_demo():
    key = RSA.generate(2048)
    public_key = key.publickey()

    message = input("Enter message to sign: ").encode()

    # sign
    h = SHA256.new(message)
    signature = pkcs1_15.new(key).sign(h)
    print("Signature (hex):", signature.hex())

    # verify
    try:
        pkcs1_15.new(public_key).verify(h, signature)
        print("Signature valid ✅")
    except (ValueError, TypeError):
        print("Signature invalid ❌")


# ==============================
# Menu
# ==============================
def main():
    while True:
        print("\n===== Cryptography Menu =====")
        print("1. Caesar Cipher (Basic Symmetric)")
        print("2. AES Encryption (Advanced Symmetric)")
        print("3. RSA Encryption/Decryption (Asymmetric)")
        print("4. Hybrid AES + RSA (Advanced Asymmetric)")
        print("5. SHA-512 Hashing")
        print("6. Digital Signature (RSA + SHA256)")
        print("7. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            msg = input("Enter message: ")
            shift = int(input("Enter shift key: "))
            enc = caesar_encrypt(msg, shift)
            print("Encrypted:", enc)
            print("Decrypted:", caesar_decrypt(enc, shift))
        elif choice == "2":
            aes_demo()
        elif choice == "3":
            rsa_demo()
        elif choice == "4":
            hybrid_demo()
        elif choice == "5":
            hash_demo()
        elif choice == "6":
            signature_demo()
        elif choice == "7":
            print("Exiting...")
            break
        else:
            print("Invalid choice! Try again.")

if __name__ == "__main__":
    main()
