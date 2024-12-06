# polyalphabetic cipher with python
def polyalphabetic_cipher(plaintext, secret_key):
    result = []
    key_length = len(secret_key)
    key_repeated = (secret_key * (len(plaintext) // key_length + 1))[:len(plaintext)]
    for i in range(len(plaintext)):
        char = plaintext[i]
        if char.isalpha():
            shift = ord(key_repeated[i].lower()) - ord('a')
            base = ord('A') if char.isupper() else ord('a')
            encrypted_char = chr((ord(char) - base + shift) % 26 + base)
            result.append(encrypted_char)
        else:
            result.append(char)
    return ''.join(result)
# An Example
plaintext = input("Enter the plaintext : ")
secret_key = input("Enter the key : ")
ciphertext = polyalphabetic_cipher(plaintext, secret_key)
print("اthe ciphertext is : ", ciphertext)