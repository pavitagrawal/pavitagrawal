from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
import base64

key = b"A1B2C3D4"
data = b"Confidential Data"

padded_data = pad(data, DES.block_size)
cipher = DES.new(key, DES.MODE_ECB)
encrypted_bytes = cipher.encrypt(padded_data)
encrypted_string = base64.b64encode(encrypted_bytes).decode('utf-8')

print("Encrypted (Base64 string):", encrypted_string)
decrypted_bytes_from_string = base64.b64decode(encrypted_string)
decrypted = unpad(cipher.decrypt(decrypted_bytes_from_string), DES.block_size)
print("Decrypted:", decrypted.decode('utf-8'))