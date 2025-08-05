from Crypto.Cipher import DES3
from Crypto.Util.Padding import pad, unpad
import base64

key = b'1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF'
data = b'Classified Text'

padded_data = pad(data, DES3.block_size)
cipher = DES3.new(key, DES3.MODE_ECB)
encrypted_bytes = cipher.encrypt(padded_data)

encrypted_string = base64.b64encode(encrypted_bytes).decode('utf-8')
print('Encrypted (Base64 string):', encrypted_string)
decrypted_bytes_from_string = base64.b64decode(encrypted_string)
decrypted = unpad(cipher.decrypt(decrypted_bytes_from_string), DES3.block_size)
print('Decrypted:', decrypted.decode('utf-8'))