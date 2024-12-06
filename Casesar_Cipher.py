def caesar_cipher_encrypt(text, shift):
   
    encrypted_text = ""
    for char in text:
        if char.isalpha():
            shift_base = ord('A') if char.isupper() else ord('a')
            encrypted_text += chr((ord(char) - shift_base + shift) % 26 + shift_base)
        else:
            encrypted_text += char
    return encrypted_text

def caesar_cipher_decrypt(text, shift):
    
    return caesar_cipher_encrypt(text, -shift)


if __name__ == "__main__":
    print(" choice the operation :")
    print("1: Encrypt")
    print("2:  Decrypt")
    choice = input(" enter the choice (1 or 2): ")

    if choice not in ["1", "2"]:
        print("invalid , try again.")
    else:
        text = input("enter text: ")
        try:
            shift_value = int(input("Enter the Key : "))
        except ValueError:
            print(" Enter integer number.")
        else:
            if choice == "1":
                result = caesar_cipher_encrypt(text, shift_value)
                print(f"text encrypt: {result}")
            else:
                result = caesar_cipher_decrypt(text, shift_value)
                print(f" text decrypt: {result}")
