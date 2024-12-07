#include <bits/stdc++.h>
using namespace std;

// Function to generate the key matrix from the key string
void getKeyMatrix(const string &key, vector<vector<int>> &keyMatrix, int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            keyMatrix[i][j] = key[k] - 'A'; // Convert character to number
            k++;
        }
    }
}

// Function to encrypt a single block of plaintext
void encrypt(vector<int> &cipherVector, const vector<vector<int>> &keyMatrix, const vector<int> &messageVector, int n) {
    for (int i = 0; i < n; i++) {
        cipherVector[i] = 0;
        for (int j = 0; j < n; j++) {
            cipherVector[i] += keyMatrix[i][j] * messageVector[j];
        }
        cipherVector[i] = (cipherVector[i] % 26 + 26) % 26; // Ensure the result is within [0, 25]
    }
}

// Function to implement Hill Cipher for any size key matrix
void HillCipher(string message, const string &key) {
    int n = sqrt(key.length()); // Determine the size of the matrix
    if (n * n != key.length()) {
        cout << "Error: Key length must be a perfect square." << endl;
        return;
    }

    // Generate the key matrix
    vector<vector<int>> keyMatrix(n, vector<int>(n));
    getKeyMatrix(key, keyMatrix, n);

    // Ensure the message length is a multiple of n
    while (message.length() % n != 0) {
        message += 'X'; // Padding with 'X'
    }

    string CipherText = "";

    // Process each block of n characters
    for (size_t block = 0; block < message.length(); block += n) {
        vector<int> messageVector(n);
        vector<int> cipherVector(n);

        // Generate vector for the message block
        for (int i = 0; i < n; i++) {
            messageVector[i] = message[block + i] - 'A'; // Convert character to number
        }

        // Encrypt the current block
        encrypt(cipherVector, keyMatrix, messageVector, n);

        // Append the encrypted block to the ciphertext
        for (int i = 0; i < n; i++) {
            CipherText += cipherVector[i] + 'A'; // Convert number back to character
        }
    }

    // Print the ciphertext
    cout << "Ciphertext: " << CipherText << endl;
}

// Driver function for the program
int main() {
    // Get the plaintext to be encrypted
    string message;
    cout << "Enter the plaintext: ";
    getline(cin, message);

    // Convert plaintext to uppercase
    for (auto &c : message) c = toupper(c);

    // Get the key
    string key;
    cout << "Enter the key (perfect square length): ";
    cin >> key;

    // Convert key to uppercase
    for (auto &c : key) c = toupper(c);

    // Call Hill Cipher
    HillCipher(message, key);

    return 0;
}
