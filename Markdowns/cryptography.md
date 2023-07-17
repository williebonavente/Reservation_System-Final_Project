# Basic Encryption Function - Caesar Cipher

## Overview

The basic encryption function used in the Airline Reservation System is a simple Caesar cipher. It is a type of substitution cipher where each character in the plaintext is shifted a fixed number of positions down the alphabet. The shift value is known as the key. In this case, the key is set to 3.

## Function Definition

1. `encryptCaesarCipher(char *text)`: Encrypts the given text using the Caesar cipher with a fixed shift value of 3.

## Implementation

```c
// Caesar Cipher Encryption
void encryptCaesarCipher(char *text)
{
    int key = 3; // Shift value for encryption

    for (int i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];

        // Encrypt uppercase characters
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ((ch - 'A') + key) % 26 + 'A';
        }
        // Encrypt lowercase characters
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ((ch - 'a') + key) % 26 + 'a';
        }

        text[i] = ch;
    }
}
