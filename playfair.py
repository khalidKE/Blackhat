def create_playfair_matrix(key):
    key = ''.join(sorted(set(key), key=key.index)).upper()
    matrix = []
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ" 
    for char in key:
        if char not in matrix and char in alphabet:
            matrix.append(char)
    for char in alphabet:
        if char not in matrix:
            matrix.append(char)
    return [matrix[i:i + 5] for i in range(0, 25, 5)] 
def format_plaintext(plaintext):
    plaintext = plaintext.replace(" ", "").upper().replace("J", "I")
    formatted = []
    i = 0
    while i < len(plaintext):
        a = plaintext[i]
        if i + 1 < len(plaintext):
            b = plaintext[i + 1]
            if a == b:
                formatted.append(a + 'X') 
                i += 1
            else:
                formatted.append(a + b)
                i += 2
        else:
            formatted.append(a + 'X')  
            i += 1
    return formatted
def find_position(matrix, char):
    for i in range(5):
        for j in range(5):
            if matrix[i][j] == char:
                return i, j
    return None
def encrypt(plaintext, key):
    matrix = create_playfair_matrix(key)
    formatted_text = format_plaintext(plaintext)
    ciphertext = ""
    for pair in formatted_text:
        row1, col1 = find_position(matrix, pair[0])
        row2, col2 = find_position(matrix, pair[1])
        if row1 == row2:  
            ciphertext += matrix[row1][(col1 + 1) % 5]
            ciphertext += matrix[row2][(col2 + 1) % 5]
        elif col1 == col2: 
            ciphertext += matrix[(row1 + 1) % 5][col1]
            ciphertext += matrix[(row2 + 1) % 5][col2]
        else:  
            ciphertext += matrix[row1][col2]
            ciphertext += matrix[row2][col1]
    return ciphertext

def decrypt(ciphertext, key):
    matrix = create_playfair_matrix(key)
    formatted_text = [ciphertext[i:i + 2] for i in range(0, len(ciphertext), 2)]
    plaintext = ""
    for pair in formatted_text:
        row1, col1 = find_position(matrix, pair[0])
        row2, col2 = find_position(matrix, pair[1])
        if row1 == row2:  
            plaintext += matrix[row1][(col1 - 1) % 5]
            plaintext += matrix[row2][(col2 - 1) % 5]
        elif col1 == col2:  
            plaintext += matrix[(row1 - 1) % 5][col1]
            plaintext += matrix[(row2 - 1) % 5][col2]
        else:  
            plaintext += matrix[row1][col2]
            plaintext += matrix[row2][col1]

    return plaintext.replace('X', '')
if __name__ == "__main__":
    mode = input("Enter '1' to encrypt or '2' to decrypt: ").strip()
    if mode == '1':
        plaintext = input("Enter the plaintext: ")
        key = input("Enter the key: ")
        encrypted = encrypt(plaintext, key)
        print(f"Encrypted: {encrypted}")
    elif mode == '2':
        ciphertext = input("Enter the ciphertext: ")
        key = input("Enter the key: ")
        decrypted = decrypt(ciphertext, key)
        print(f"Decrypted: {decrypted}")
    else:
        print("Invalid mode selected. Please enter '1' for encryption or '2' for decryption.")