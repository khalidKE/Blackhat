#include <bits/stdc++.h>
using namespace std;

// Function to find modular inverse of a number under modulo 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to calculate the determinant of a matrix modulo 26
int determinant(const vector<vector<int>> &matrix, int n) {
    if (n == 1) return matrix[0][0];
    if (n == 2)
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;

    int det = 0;
    for (int col = 0; col < n; col++) {
        vector<vector<int>> submatrix(n - 1, vector<int>(n - 1));
        for (int i = 1; i < n; i++) {
            int sub_col = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                submatrix[i - 1][sub_col++] = matrix[i][j];
            }
        }
        det += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * determinant(submatrix, n - 1);
        det = (det % 26 + 26) % 26; // Ensure positive mod 26
    }
    return det;
}

// Function to calculate the adjoint of a matrix
void adjoint(const vector<vector<int>> &matrix, vector<vector<int>> &adj, int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<int>> submatrix(n - 1, vector<int>(n - 1));
            for (int x = 0; x < n; x++) {
                if (x == i) continue;
                for (int y = 0; y < n; y++) {
                    if (y == j) continue;
                    submatrix[x < i ? x : x - 1][y < j ? y : y - 1] = matrix[x][y];
                }
            }
            adj[j][i] = (determinant(submatrix, n - 1) * ((i + j) % 2 == 0 ? 1 : -1)) % 26;
            adj[j][i] = (adj[j][i] + 26) % 26; // Ensure positive mod 26
        }
    }
}

// Function to find the inverse of a matrix modulo 26
bool inverseMatrix(const vector<vector<int>> &matrix, vector<vector<int>> &inverse, int n) {
    int det = determinant(matrix, n);
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        cout << "Matrix is not invertible under mod 26." << endl;
        return false;
    }

    vector<vector<int>> adj(n, vector<int>(n));
    adjoint(matrix, adj, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = (adj[i][j] * detInv) % 26;
            inverse[i][j] = (inverse[i][j] + 26) % 26; // Ensure positive mod 26
        }
    }
    return true;
}

// Function to decrypt a single block
void decrypt(vector<int> &plainVector, const vector<vector<int>> &invKeyMatrix, const vector<int> &cipherVector, int n) {
    for (int i = 0; i < n; i++) {
        plainVector[i] = 0;
        for (int j = 0; j < n; j++) {
            plainVector[i] += invKeyMatrix[i][j] * cipherVector[j];
        }
        plainVector[i] = (plainVector[i] % 26 + 26) % 26;
    }
}

// Hill Cipher Decryption Function
void HillCipherDecrypt(string cipherText, const string &key) {
    int n = sqrt(key.length());
    if (n * n != key.length()) {
        cout << "Error: Key length must be a perfect square." << endl;
        return;
    }

    vector<vector<int>> keyMatrix(n, vector<int>(n));
    vector<vector<int>> invKeyMatrix(n, vector<int>(n));

    // Populate key matrix
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            keyMatrix[i][j] = key[k++] - 'A';
        }
    }

    // Calculate the inverse key matrix
    if (!inverseMatrix(keyMatrix, invKeyMatrix, n)) {
        cout << "Decryption failed: Key matrix is not invertible." << endl;
        return;
    }

    // Decrypt the cipher text
    string plainText = "";
    for (size_t block = 0; block < cipherText.length(); block += n) {
        vector<int> cipherVector(n);
        vector<int> plainVector(n);

        for (int i = 0; i < n; i++) {
            cipherVector[i] = cipherText[block + i] - 'A';
        }

        decrypt(plainVector, invKeyMatrix, cipherVector, n);

        for (int i = 0; i < n; i++) {
            plainText += plainVector[i] + 'A';
        }
    }

    cout << "Plaintext: " << plainText << endl;
}

// Main function
int main() {
    string cipherText , key;

    cout << "Enter the ciphertext: ";
    cin >> cipherText;

    cout << "Enter the key (perfect square length): ";
    cin >> key;

    for (auto &c : cipherText) 
        c = toupper(c);
    for (auto &c : key) 
        c = toupper(c);

    HillCipherDecrypt(cipherText, key);

    return 0;
}
