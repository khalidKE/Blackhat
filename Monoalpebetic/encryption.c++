#include <bits/stdc++.h>
using namespace std;

// Function to generate substitution map
void generateSubstitutionMap(const string &key, unordered_map<char, char> &encryptMap) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Create encryption map
    for (size_t i = 0; i < alphabet.size(); i++) {
        encryptMap[alphabet[i]] = key[i];
    }
}

// Function to encrypt plaintext
string encrypt(const string &plaintext, const unordered_map<char, char> &encryptMap) {
    string ciphertext = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char upperChar = toupper(ch);
            ciphertext += encryptMap.at(upperChar);
        } else {
            ciphertext += ch; // Non-alphabetic characters remain unchanged
        }
    }
    return ciphertext;
}

int main() {
    string key, plaintext, ciphertext;
    
    // Define substitution key (should be 26 unique uppercase letters)
    cout << "Enter a 26-character substitution key: ";
    cin >> key;

    // Validate key length
    if (key.size() != 26) {
        cout << "Error: Key must be exactly 26 characters long." << endl;
        return 1;
    }

    // Convert key to uppercase for consistency
    for (char &ch : key) ch = toupper(ch);

    // Generate substitution map
    unordered_map<char, char> encryptMap;
    generateSubstitutionMap(key, encryptMap);

    // Input plaintext
    cout << "Enter plaintext: ";
    cin.ignore();
    getline(cin, plaintext);

    // Encrypt the plaintext
    ciphertext = encrypt(plaintext, encryptMap);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}

