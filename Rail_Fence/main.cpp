#include<bits/stdc++.h>
using namespace  std  ;
string encryptRailFence(string message, int key)
{
    if (key <= 1) return message;
    string rails[key];
    int direction = 1;
    int row = 0;
    for (int i  = 0 ; i < message.size() ; i++)
    {
        rails[row] += message[i];
        row += direction;
        if (row == 0 || row == key - 1)
        {
            direction *=-1 ;
        }
    }
    string cipher="";
    for (int i = 0 ; i< key  ; i++)cipher +=rails[i] ;
    return cipher;
}
string decryptRailFence(string cipher, int key)
{
    if (key <= 1) return cipher;
   int  pattern[cipher.size()];
    int direction = 1;
    int row = 0;
    for (int i = 0; i < cipher.size(); ++i)
    {
        pattern[i] = row;
        row += direction;
        if (row == 0 || row == key - 1)
        {
            direction *=-1 ;
        }
    }
   string rails[key];
    int  index = 0;
    for (int r = 0; r < key; ++r)
    {
        for (int  i = 0; i < cipher.size(); ++i)
        {
            if (pattern[i] == r)
            {
                rails[r] += cipher[index++];
            }
        }
    }
    string message;
    row = 0;
    for (int i = 0; i < cipher.size(); ++i)
    {
        message += rails[row][0];
        rails[row].erase(0, 1);
        row += direction;

        if (row == 0 || row == key - 1)
        {
            direction *=-1 ;
        }
    }

    return message;
}
int main()
{
    string message;
    int key;
    cout << "Enter the message to encrypt: ";
    getline(cin, message);
    cout << "Enter the key (number of rails): " ;
    cin >> key;
    string cipher = encryptRailFence(message, key);
    cout << "\nEncrypted Message: " << cipher <<endl;
    string DE = decryptRailFence(cipher, key);
    cout << "Decrypted Message: " << DE << endl ;
    return 0;
}
