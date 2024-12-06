# row column encryption and decryption with python
import math
def create_matrix(plaintext, key):
    plaintext = plaintext.replace(" ", "")
    num_cols = len(key)
    num_rows = math.ceil(len(plaintext)/ num_cols)  # ceil division
    matrix = [[''] * num_cols for _ in range(num_rows)]
    index = 0
    for r in range(num_rows):
        for c in range(num_cols):
            if index < len(plaintext):
                matrix[r][c] = plaintext[index]
                index += 1
            else:
                matrix[r][c] = 'X'
    return matrix
# Encryption function...
def encrypt(plaintext, key):
    matrix = create_matrix(plaintext, key)
    key_order = sorted(range(len(key)), key=lambda k: key[k])
    ciphertext = ''
    for col in key_order:
        for row in range(len(matrix)):
            ciphertext += matrix[row][col]
    return ciphertext
# Decryption function...
def decrypt(ciphertext, key):
    num_cols = len(key)
    num_rows = len(ciphertext) // num_cols
    matrix = [[''] * num_cols for _ in range(num_rows)]
    key_order = sorted(range(len(key)), key=lambda k: key[k])
    index = 0
    for col in key_order:
        for row in range(num_rows):
            if index < len(ciphertext):
                matrix[row][col] = ciphertext[index]
                index += 1
    plaintext = ''
    for r in range(num_rows):
        for c in range(num_cols):
            plaintext += matrix[r][c]
    return plaintext.rstrip('X')
# An Example....
plaintext = input("Enter the plaintext : ")
key = input("Enter the key : ")
Ciphertext = encrypt(plaintext, key)
print("Ciphertext : ", Ciphertext)
plaintext = decrypt(Ciphertext, key)
print("plaintext : ", plaintext)