#include<bits/stdc++.h>
using namespace std ;
/*
p ^ k ---->  c
c ^ k ---->  p
*/
string KEY(string message) {
   string key;srand(time(nullptr));
    for (auto  c : message)key += static_cast<char>(rand() % 256); // typing casting(convert number to  char)
    return key;
}
/*
steps this alg (EN)
1-  generate random map(key)
2-  convert each  letter to number in key  and message  using ASCII
3-  using operation XOR between two  number one form  message and other from  key
4-  value(number)  result from  operation  convert  to char  from ASCII
*/
string encrypt(string message, string key) {
    string cipher;
    for (int  i = 0; i < message.size(); ++i) cipher += message[i] ^ key[i];
    return cipher;
}
/*
steps this alg (DE)
1-  convert each  letter to number in key  and Chiper  using ASCII
2-  using operation XOR between two  number one form  chiper and other from  key
3-  value(number)  result from  operation  convert  to char  from ASCII
*/
string decrypt(string cipher, string key) {
    string message;
    for (int i = 0; i < cipher.size(); ++i) message += cipher[i] ^ key[i];
    return message;
}
int main() {
    string message;
    cout << "Enter the message to encrypt: ";
    getline(cin, message);
    string key = KEY(message);
    string cipher = encrypt(message, key);
    cout << "Encrypted Message: " << cipher <<endl ;
    string DE = decrypt(cipher, key);
    cout << "Decrypted Message: " << DE <<endl ;
    return 0;
}
