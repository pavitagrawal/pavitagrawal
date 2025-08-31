import time
import matplotlib.pyplot as plt
from Crypto.Cipher import AES, DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import random
from sympy import isprime, randprime

# -------------------------------
# 1. Playfair Cipher
# -------------------------------
def generate_playfair_key_matrix(key):
    key = key.upper().replace("J", "I")
    matrix = []
    used = set()

    for char in key:
        if char not in used and char.isalpha():
            used.add(char)
            matrix.append(char)

    for char in "ABCDEFGHIKLMNOPQRSTUVWXYZ":
        if char not in used:
            used.add(char)
            matrix.append(char)

    return [matrix[i:i+5] for i in range(0, 25, 5)]

def playfair_process_text(text):
    text = text.upper().replace("J", "I")
    processed = ""
    i = 0
    while i < len(text):
        a = text[i]
        b = text[i+1] if i+1 < len(text) else "X"
        if a == b:
            processed += a + "X"
            i += 1
        else:
            processed += a + b
            i += 2
    if len(processed) % 2 != 0:
        processed += "X"
    return processed

def playfair_encrypt(plaintext, matrix):
    plaintext = playfair_process_text(plaintext)
    ciphertext = ""
    for i in range(0, len(plaintext), 2):
        a, b = plaintext[i], plaintext[i+1]
        row_a, col_a = [(r, c) for r in range(5) for c in range(5) if matrix[r][c] == a][0]
        row_b, col_b = [(r, c) for r in range(5) for c in range(5) if matrix[r][c] == b][0]

        if row_a == row_b:
            ciphertext += matrix[row_a][(col_a+1)%5] + matrix[row_b][(col_b+1)%5]
        elif col_a == col_b:
            ciphertext += matrix[(row_a+1)%5][col_a] + matrix[(row_b+1)%5][col_b]
        else:
            ciphertext += matrix[row_a][col_b] + matrix[row_b][col_a]
    return ciphertext

def playfair_decrypt(ciphertext, matrix):
    plaintext = ""
    for i in range(0, len(ciphertext), 2):
        a, b = ciphertext[i], ciphertext[i+1]
        row_a, col_a = [(r, c) for r in range(5) for c in range(5) if matrix[r][c] == a][0]
        row_b, col_b = [(r, c) for r in range(5) for c in range(5) if matrix[r][c] == b][0]

        if row_a == row_b:
            plaintext += matrix[row_a][(col_a-1)%5] + matrix[row_b][(col_b-1)%5]
        elif col_a == col_b:
            plaintext += matrix[(row_a-1)%5][col_a] + matrix[(row_b-1)%5][col_b]
        else:
            plaintext += matrix[row_a][col_b] + matrix[row_b][col_a]
    return plaintext

# -------------------------------
# 2. AES
# -------------------------------
def aes_encrypt_decrypt():
    key_size = int(input("Enter AES key size (128, 192, 256): ")) // 8
    key = get_random_bytes(key_size)
    plaintext = input("Enter plaintext: ").encode()

    cipher = AES.new(key, AES.MODE_CBC)
    ct_bytes = cipher.encrypt(pad(plaintext, AES.block_size))
    iv = cipher.iv

    cipher_dec = AES.new(key, AES.MODE_CBC, iv)
    pt = unpad(cipher_dec.decrypt(ct_bytes), AES.block_size)

    print("Ciphertext:", ct_bytes.hex())
    print("Decrypted:", pt.decode())

# -------------------------------
# 3. RSA
# -------------------------------
def generate_rsa_keys():
    p = randprime(100, 300)
    q = randprime(100, 300)
    n = p * q
    phi = (p-1)*(q-1)

    e = 65537
    while phi % e == 0:
        e = random.randrange(2, phi)

    d = pow(e, -1, phi)

    return (e, n), (d, n)

def rsa_encrypt_decrypt():
    public, private = generate_rsa_keys()
    msg = int(input("Enter a number to encrypt (small integer): "))

    enc = pow(msg, public[0], public[1])
    dec = pow(enc, private[0], private[1])

    print("Public Key:", public)
    print("Private Key:", private)
    print("Encrypted:", enc)
    print("Decrypted:", dec)

# -------------------------------
# 4. Performance AES vs DES
# -------------------------------
def performance_comparison():
    data = b"A"*1000000  # 1 MB data

    # AES
    aes_key = get_random_bytes(16)
    cipher_aes = AES.new(aes_key, AES.MODE_ECB)
    start = time.time()
    ct_aes = cipher_aes.encrypt(pad(data, AES.block_size))
    cipher_aes.decrypt(ct_aes)
    end = time.time()
    aes_time = end - start

    # DES
    des_key = get_random_bytes(8)
    cipher_des = DES.new(des_key, DES.MODE_ECB)
    start = time.time()
    ct_des = cipher_des.encrypt(pad(data, DES.block_size))
    cipher_des.decrypt(ct_des)
    end = time.time()
    des_time = end - start

    print(f"AES time: {aes_time:.4f}s")
    print(f"DES time: {des_time:.4f}s")

    # Visualization
    plt.bar(["AES", "DES"], [aes_time, des_time], color=['blue', 'orange'])
    plt.ylabel("Time (seconds)")
    plt.title("AES vs DES Performance")
    plt.show()

# -------------------------------
# Menu
# -------------------------------
def main():
    while True:
        print("\n=== MENU ===")
        print("1. Playfair Cipher")
        print("2. AES Encryption/Decryption")
        print("3. RSA Encryption/Decryption")
        print("4. AES vs DES Performance")
        print("5. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            key = input("Enter Playfair key: ")
            text = input("Enter plaintext: ")
            matrix = generate_playfair_key_matrix(key)
            ct = playfair_encrypt(text, matrix)
            print("Encrypted:", ct)
            print("Decrypted:", playfair_decrypt(ct, matrix))
        elif choice == "2":
            aes_encrypt_decrypt()
        elif choice == "3":
            rsa_encrypt_decrypt()
        elif choice == "4":
            performance_comparison()
        elif choice == "5":
            break
        else:
            print("Invalid choice, try again.")

if __name__ == "__main__":
    main()

