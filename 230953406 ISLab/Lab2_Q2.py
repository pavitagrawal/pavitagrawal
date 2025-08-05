from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import base64

key = b"0123456789ABCDEF0123456789ABCDEF"
data = b"Sensitive Information"

padded_data = pad(data, AES.block_size)
cipher = AES.new(key, AES.MODE_ECB)
encrypted_bytes = cipher.encrypt(padded_data)
encrypted_string = base64.b64encode(encrypted_bytes).decode('utf-8')

print("Encrypted (Base64 string):", encrypted_string)
decrypted_bytes_from_string = base64.b64decode(encrypted_string)
decrypted = unpad(cipher.decrypt(decrypted_bytes_from_string), AES.block_size)
print("Decrypted:", decrypted.decode('utf-8'))