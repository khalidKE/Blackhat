#include <bits/stdc++.h>
using namespace std;
// Function to decrypt the ciphertext using the monoalphabetic cipher
string monoalphabeticDecrypt(string ciphertext, string key) {
    string plaintext = "";
    // Create a reverse map of the key to easily find the corresponding letter for decryption
    string reverseKey(26, ' ');
    for (int i = 0; i < 26; ++i) {
        reverseKey[key[i] - 'A'] = 'A' + i;
    }

    for (char ch : ciphertext) {
        // Check if the character is an alphabet
        if (isalpha(ch)) {
            // Convert the character to lowercase for ease of processing
            char base = islower(ch) ? 'a' : 'A';
            // Find the original letter using the reverse key
            char decryptedChar = reverseKey[tolower(ch) - 'a'];
            // Add the decrypted character to the plaintext
            plaintext += islower(ch) ? tolower(decryptedChar) : toupper(decryptedChar);
        } else {
            // If the character is not an alphabet, add it as is
            plaintext += ch;
        }
    }
    return plaintext;
}

int main() {
    string ciphertext;
    string key;

    // Input the ciphertext and the key
    cout << "Enter the ciphertext: ";
    getline(cin, ciphertext);
    cout << "Enter the key (26 characters, no duplicates): ";
    getline(cin, key);

    // Check if the key length is valid
    if (key.length() != 26) {
        cout << "Error: Key must be 26 characters long." << endl;
        return 1;
    }
    
    // Check if the key contains duplicate characters
    bool hasDuplicates = false;
    for (int i = 0; i < key.length(); ++i) {
        for (int j = i + 1; j < key.length(); ++j) {
            if (key[i] == key[j]) {
                hasDuplicates = true;
                break;
            }
        }
        if (hasDuplicates) break;
    }

    if (hasDuplicates) {
        cout << "Error: Key must not have duplicate characters." << endl;
        return 1;
    }

    // Decrypt the ciphertext using the key
    string plaintext = monoalphabeticDecrypt(ciphertext, key);

    // Output the decrypted plaintext
    cout << "Plaintext: " << plaintext << endl;

    return 0;
}
