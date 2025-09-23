import base64
import hashlib
import json
import time
from dataclasses import dataclass, asdict
from datetime import datetime
from typing import List, Any

from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

# Helper dataclasses & types

class PatientRecord:
    def __init__(self, timestamp, aes_encrypted_data_b64, rsa_encrypted_aes_key_hex,
                 sha512_hash_hex, iv_hex, data_fields_preview=None):
        self.timestamp = timestamp
        self.aes_encrypted_data_b64 = aes_encrypted_data_b64
        self.rsa_encrypted_aes_key_hex = rsa_encrypted_aes_key_hex
        self.sha512_hash_hex = sha512_hash_hex  # hash of the patient's name
        self.iv_hex = iv_hex  # AES IV (if used)
        # keep original length maybe for debugging (not necessary in real world)
        self.data_fields_preview = data_fields_preview  # only for demonstration

class DoctorVerification:
    def __init__(self, timestamp, patient_index, verified_name_hash_hex, verification_note):
        self.timestamp = timestamp
        self.patient_index = patient_index
        self.verified_name_hash_hex = verified_name_hash_hex
        self.verification_note = verification_note


# Crypto utilities

def generate_rsa_keypair(bits: int = 2048):
    key = RSA.generate(bits)
    return key, key.publickey()


def aes_encrypt(plaintext_bytes: bytes, key_bytes: bytes):
    """
    AES-CBC encryption with random IV; returns (iv, ciphertext)
    """
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(key_bytes, AES.MODE_CBC, iv=iv)
    padded = pad(plaintext_bytes, AES.block_size)
    ct = cipher.encrypt(padded)
    return iv, ct


def aes_decrypt(iv: bytes, ciphertext: bytes, key_bytes: bytes):
    cipher = AES.new(key_bytes, AES.MODE_CBC, iv=iv)
    pt_padded = cipher.decrypt(ciphertext)
    pt = unpad(pt_padded, AES.block_size)
    return pt


def rsa_encrypt_bytes(message_bytes: bytes, pub_key: RSA.RsaKey):
    cipher = PKCS1_OAEP.new(pub_key)
    ct = cipher.encrypt(message_bytes)
    return ct


def rsa_decrypt_bytes(ciphertext: bytes, priv_key: RSA.RsaKey):
    cipher = PKCS1_OAEP.new(priv_key)
    pt = cipher.decrypt(ciphertext)
    return pt


def sha512_hex(data: bytes):
    h = hashlib.sha512()
    h.update(data)
    return h.hexdigest()


def now_timestamp_str():
    return datetime.now().isoformat(sep=' ', timespec='seconds')


# Global lists (in-memory store)

patient_records: List[PatientRecord] = []
doctor_verifications: List[DoctorVerification] = []

# We'll generate one RSA keypair representing the hospital/doctor authority.
RSA_PRIV, RSA_PUB = generate_rsa_keypair(2048)


# Patient module

def patient_module_demo(interactive: bool = True):
    """
    Takes patient details, encrypts with AES, encrypts AES key with RSA, creates SHA-512 hash for the name,
    stores the PatientRecord with timestamp.
    Also measures execution times for AES encryption, RSA encryption, and SHA-512 hashing.
    Returns a dict of timings for this record.
    """
    # Accept input fields
    if interactive:
        print("\n--- Patient Module ---")
        name = input("Enter patient name (default: 'John Doe'): ") or "John Doe"
        age = input("Enter patient age (default: '30'): ") or "30"
        gender = input("Enter patient gender (default: 'M'): ") or "M"
        diagnosis = input("Enter diagnosis (default: 'Hypertension'): ") or "Hypertension"
        notes = input("Enter any notes (default: 'No allergies'): ") or "No allergies"
    else:
        # default demo data
        name, age, gender, diagnosis, notes = "John Doe", "30", "M", "Hypertension", "No allergies"

    # Build a JSON plaintext (bytes)
    patient_data = {
        "name": name,
        "age": age,
        "gender": gender,
        "diagnosis": diagnosis,
        "notes": notes
    }
    plaintext_bytes = json.dumps(patient_data, ensure_ascii=False).encode('utf-8')

    # 1) AES encryption (generate random 32-byte key for AES-256)
    aes_key = get_random_bytes(32)

    start_aes = time.perf_counter()
    iv, aes_ct = aes_encrypt(plaintext_bytes, aes_key)
    end_aes = time.perf_counter()
    aes_elapsed = end_aes - start_aes

    aes_ct_b64 = base64.b64encode(aes_ct).decode('utf-8')
    iv_hex = iv.hex()

    print("\n[Patient] Plaintext JSON:")
    print(json.dumps(patient_data, indent=2, ensure_ascii=False))
    print("\n[Patient] AES key (hex) (shown FOR DEMO; keep secret):", aes_key.hex())
    print("[Patient] AES IV (hex):", iv_hex)
    print("[Patient] AES ciphertext (Base64):", aes_ct_b64)
    print(f"[Patient] AES encryption time: {aes_elapsed:.6f} seconds")

    # 2) RSA encryption of AES key (using hospital/public key)
    start_rsa = time.perf_counter()
    rsa_encrypted_key = rsa_encrypt_bytes(aes_key, RSA_PUB)
    end_rsa = time.perf_counter()
    rsa_elapsed = end_rsa - start_rsa

    rsa_enc_key_hex = rsa_encrypted_key.hex()
    print("\n[Patient] RSA-encrypted AES key (hex):", rsa_enc_key_hex)
    print(f"[Patient] RSA encryption time: {rsa_elapsed:.6f} seconds")

    # 3) SHA-512 hash of patient's name
    start_hash = time.perf_counter()
    name_hash_hex = sha512_hex(name.encode('utf-8'))
    end_hash = time.perf_counter()
    hash_elapsed = end_hash - start_hash

    print("\n[Patient] SHA-512 hash of patient name (hex):", name_hash_hex)
    print(f"[Patient] SHA-512 hashing time: {hash_elapsed:.6f} seconds")

    # 4) Store record with timestamp in patient_records
    record = PatientRecord(
        timestamp=now_timestamp_str(),
        aes_encrypted_data_b64=aes_ct_b64,
        rsa_encrypted_aes_key_hex=rsa_enc_key_hex,
        sha512_hash_hex=name_hash_hex,
        iv_hex=iv_hex,
        data_fields_preview={"name": name, "age": age}  # demonstration only — don't store plaintext in real systems
    )
    patient_records.append(record)

    print("\n[Patient] Stored PatientRecord (appended to patient_records):")
    print(json.dumps(asdict(record), indent=2))

    return {
        "aes_time": aes_elapsed,
        "rsa_time": rsa_elapsed,
        "hash_time": hash_elapsed
    }


# Doctor module

def doctor_module_demo(record_index: int = None):
    """
    Doctor retrieves a patient record by index (0-based), decrypts the AES key with RSA private key,
    decrypts the patient data, verifies the SHA-512 hash of the patient's name, re-hashes the name and stores
    verification in doctor_verifications list with timestamp.
    Also measures the times for RSA decryption, AES decryption, and SHA-512 verification hashing.
    """
    print("\n--- Doctor Module ---")
    if not patient_records:
        print("[Doctor] No patient records available.")
        return None

    if record_index is None:
        # show available indices
        print(f"[Doctor] There are {len(patient_records)} patient record(s). Index range: 0 .. {len(patient_records)-1}")
        try:
            idx_input = input("Enter patient record index to retrieve (default 0): ").strip()
            record_index = int(idx_input) if idx_input != "" else 0
        except Exception:
            record_index = 0

    if record_index < 0 or record_index >= len(patient_records):
        print("[Doctor] Invalid index.")
        return None

    record = patient_records[record_index]
    print(f"\n[Doctor] Fetching PatientRecord at index {record_index}:")
    print(json.dumps(asdict(record), indent=2))

    # Convert stored fields back to bytes
    aes_ct = base64.b64decode(record.aes_encrypted_data_b64)
    iv = bytes.fromhex(record.iv_hex)
    rsa_encrypted_key = bytes.fromhex(record.rsa_encrypted_aes_key_hex)

    # RSA decrypt AES key (doctor has RSA_PRIV)
    start_rsa_dec = time.perf_counter()
    try:
        decrypted_aes_key = rsa_decrypt_bytes(rsa_encrypted_key, RSA_PRIV)
    except Exception as e:
        print("[Doctor] RSA decryption failed:", e)
        return None
    end_rsa_dec = time.perf_counter()
    rsa_dec_time = end_rsa_dec - start_rsa_dec
    print("\n[Doctor] RSA-decrypted AES key (hex):", decrypted_aes_key.hex())
    print(f"[Doctor] RSA decryption time: {rsa_dec_time:.6f} seconds")

    # AES decrypt data
    start_aes_dec = time.perf_counter()
    try:
        plaintext_bytes = aes_decrypt(iv, aes_ct, decrypted_aes_key)
    except Exception as e:
        print("[Doctor] AES decryption failed:", e)
        return None
    end_aes_dec = time.perf_counter()
    aes_dec_time = end_aes_dec - start_aes_dec
    plaintext_json = plaintext_bytes.decode('utf-8')
    try:
        plaintext_obj = json.loads(plaintext_json)
    except Exception:
        plaintext_obj = {"raw": plaintext_json}

    print("\n[Doctor] Decrypted patient JSON:")
    print(json.dumps(plaintext_obj, indent=2, ensure_ascii=False))
    print(f"[Doctor] AES decryption time: {aes_dec_time:.6f} seconds")

    # Verify integrity by checking SHA-512 hash of the patient's name
    start_hash_verify = time.perf_counter()
    computed_name_hash = sha512_hex(plaintext_obj.get("name", "").encode('utf-8'))
    end_hash_verify = time.perf_counter()
    hash_verify_time = end_hash_verify - start_hash_verify

    print("\n[Doctor] Stored name hash (hex) in PatientRecord:", record.sha512_hash_hex)
    print("[Doctor] Computed name hash (hex) from decrypted data:", computed_name_hash)
    hash_matches = (computed_name_hash == record.sha512_hash_hex)
    print("[Doctor] Hash match result:", hash_matches)
    print(f"[Doctor] SHA-512 verification hashing time: {hash_verify_time:.6f} seconds")

    # Re-hash the name (simulate doctor's separate log) and store in doctor_verifications
    verification_hash = sha512_hex(plaintext_obj.get("name", "").encode('utf-8'))
    verification = DoctorVerification(
        timestamp=now_timestamp_str(),
        patient_index=record_index,
        verified_name_hash_hex=verification_hash,
        verification_note=f"Verified by doctor; integrity={'OK' if hash_matches else 'FAILED'}"
    )
    doctor_verifications.append(verification)

    print("\n[Doctor] Appended DoctorVerification entry:")
    print(json.dumps(asdict(verification), indent=2))

    return {
        "rsa_decrypt_time": rsa_dec_time,
        "aes_decrypt_time": aes_dec_time,
        "hash_verify_time": hash_verify_time,
        "hash_matches": hash_matches
    }


# Auditor module

def auditor_module_demo():
    """
    Auditor can encrypt (with a new AES key) and decrypt both the patient_records list and the doctor's verification list.
    We'll:
      - Serialize each list to JSON (for demo)
      - Use AES-CBC with a random key per list
      - Show encrypted Base64, then decrypt and show recovered JSON
    Measures AES encryption/decryption times for both lists and prints outputs.
    """
    print("\n--- Auditor Module ---")

    # Prepare serializations
    patient_list_json = json.dumps([asdict(r) for r in patient_records], indent=2, ensure_ascii=False).encode('utf-8')
    doctor_list_json = json.dumps([asdict(d) for d in doctor_verifications], indent=2, ensure_ascii=False).encode('utf-8')

    # Audit: encrypt patient_records list
    patient_aes_key = get_random_bytes(32)
    start_p_aes_enc = time.perf_counter()
    p_iv, p_ct = aes_encrypt(patient_list_json, patient_aes_key)
    end_p_aes_enc = time.perf_counter()
    p_aes_enc_time = end_p_aes_enc - start_p_aes_enc

    p_ct_b64 = base64.b64encode(p_ct).decode('utf-8')
    print("\n[Auditor] Encrypted patient_records list (Base64):")
    print(p_ct_b64)
    print("[Auditor] Patient-list AES IV (hex):", p_iv.hex())
    print("[Auditor] Patient-list AES key (hex) (shown FOR DEMO):", patient_aes_key.hex())
    print(f"[Auditor] Patient-list AES encryption time: {p_aes_enc_time:.6f} seconds")

    # Audit: decrypt patient_records list
    start_p_aes_dec = time.perf_counter()
    p_decrypted = aes_decrypt(p_iv, base64.b64decode(p_ct_b64), patient_aes_key)
    end_p_aes_dec = time.perf_counter()
    p_aes_dec_time = end_p_aes_dec - start_p_aes_dec
    print("\n[Auditor] Decrypted patient_records JSON (recovered):")
    try:
        p_decrypted_obj = json.loads(p_decrypted.decode('utf-8'))
        print(json.dumps(p_decrypted_obj, indent=2, ensure_ascii=False))
    except Exception:
        print(p_decrypted.decode('utf-8'))
    print(f"[Auditor] Patient-list AES decryption time: {p_aes_dec_time:.6f} seconds")

    # Audit: encrypt doctor_verifications list
    doctor_aes_key = get_random_bytes(32)
    start_d_aes_enc = time.perf_counter()
    d_iv, d_ct = aes_encrypt(doctor_list_json, doctor_aes_key)
    end_d_aes_enc = time.perf_counter()
    d_aes_enc_time = end_d_aes_enc - start_d_aes_enc

    d_ct_b64 = base64.b64encode(d_ct).decode('utf-8')
    print("\n[Auditor] Encrypted doctor_verifications list (Base64):")
    print(d_ct_b64)
    print("[Auditor] Doctor-list AES IV (hex):", d_iv.hex())
    print("[Auditor] Doctor-list AES key (hex) (shown FOR DEMO):", doctor_aes_key.hex())
    print(f"[Auditor] Doctor-list AES encryption time: {d_aes_enc_time:.6f} seconds")

    # Audit: decrypt doctor_verifications list
    start_d_aes_dec = time.perf_counter()
    d_decrypted = aes_decrypt(d_iv, base64.b64decode(d_ct_b64), doctor_aes_key)
    end_d_aes_dec = time.perf_counter()
    d_aes_dec_time = end_d_aes_dec - start_d_aes_dec
    print("\n[Auditor] Decrypted doctor_verifications JSON (recovered):")
    try:
        d_decrypted_obj = json.loads(d_decrypted.decode('utf-8'))
        print(json.dumps(d_decrypted_obj, indent=2, ensure_ascii=False))
    except Exception:
        print(d_decrypted.decode('utf-8'))
    print(f"[Auditor] Doctor-list AES decryption time: {d_aes_dec_time:.6f} seconds")

    return {
        "patient_list_aes_enc_time": p_aes_enc_time,
        "patient_list_aes_dec_time": p_aes_dec_time,
        "doctor_list_aes_enc_time": d_aes_enc_time,
        "doctor_list_aes_dec_time": d_aes_dec_time
    }


# Small interactive menu to demo full workflow

def print_menu():
    print("\n\n=== Cryptography Workflow Demo ===")
    print("1) Add patient record (Patient Module)")
    print("2) View stored patient records (list indices)")
    print("3) Doctor: retrieve & verify a patient record by index")
    print("4) View doctor verification log")
    print("5) Auditor: encrypt & decrypt both lists (demo)")
    print("6) Show timing comparison summary (last operation)")
    print("7) Exit")
    print("Choose an option (1-7): ", end='')


def view_patient_records():
    print("\n--- Patient Records (SUMMARY) ---")
    if not patient_records:
        print("No patient records.")
        return
    for i, rec in enumerate(patient_records):
        summary = {
            "index": i,
            "timestamp": rec.timestamp,
            "aes_ct_preview": rec.aes_encrypted_data_b64[:60] + ("..." if len(rec.aes_encrypted_data_b64) > 60 else ""),
            "rsa_key_ct_preview": rec.rsa_encrypted_aes_key_hex[:60] + ("..." if len(rec.rsa_encrypted_aes_key_hex) > 60 else ""),
            "sha512_hash": rec.sha512_hash_hex[:20] + "..."
        }
        print(json.dumps(summary, indent=2))


def view_doctor_verifications():
    print("\n--- Doctor Verifications ---")
    if not doctor_verifications:
        print("No verifications.")
        return
    for i, v in enumerate(doctor_verifications):
        print(f"Index {i}: {json.dumps(asdict(v), indent=2)}")


def main_loop():
    last_timings = {}
    while True:
        print_menu()
        choice = input().strip()
        if choice == "1":
            timings = patient_module_demo(interactive=True)
            last_timings.update(timings or {})
        elif choice == "2":
            view_patient_records()
        elif choice == "3":
            # call doctor module
            timings = doctor_module_demo()
            if timings:
                last_timings.update(timings)
        elif choice == "4":
            view_doctor_verifications()
        elif choice == "5":
            timings = auditor_module_demo()
            last_timings.update(timings or {})
        elif choice == "6":
            # print a helpful timing summary if present
            print("\n--- Timing Comparison Summary (most recent operations) ---")
            if not last_timings:
                print("No timing data collected yet. Perform operations first.")
            else:
                # Friendly table-like print
                for k, v in last_timings.items():
                    print(f"{k}: {v:.6f} seconds")
                # Try to compare AES vs RSA vs SHA if present
                aes_time = last_timings.get("aes_time") or last_timings.get("aes_decrypt_time") or last_timings.get("aes_encrypt_time")
                rsa_time = last_timings.get("rsa_time") or last_timings.get("rsa_decrypt_time")
                sha_time = last_timings.get("hash_time") or last_timings.get("hash_verify_time")
                if aes_time and rsa_time and sha_time:
                    print("\nRough comparison (smaller is faster):")
                    times = [("AES", aes_time), ("RSA", rsa_time), ("SHA-512", sha_time)]
                    times_sorted = sorted(times, key=lambda x: x[1])
                    for name, t in times_sorted:
                        print(f"{name}: {t:.6f} s")
                else:
                    print("(Not enough data to compare AES/RSA/SHA directly. Perform patient and doctor operations to collect data.)")
        elif choice == "7":
            print("Exiting. Goodbye.")
            break
        else:
            print("Invalid choice. Try again.")

# If run as main script, start interactive demo

if __name__ == "__main__":
    print("Starting Cryptography Workflow Demo (Patient / Doctor / Auditor).")
    print("RSA public key modulus (n) preview (hex):", hex(RSA_PUB.n)[:80] + "...")
    main_loop()
