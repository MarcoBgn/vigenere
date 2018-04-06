// Generates ciphertext using Ci = (Pi + kj) mod 26
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
// A_SIZE: size of the alphabet
#define A_SIZE 26
// ASCII_OFFSET: Used to set a/A to 0, b/B to 1, etc.
#define ASCII_OFFSET 97
#define ASCII_LAST_UP 90
#define ASCII_LAST_LO 122
// Checks if the argument count and key are valid
bool args_valid(int argc, string key);
// Adds the cyper and returns an integer
int calc_cipher(int character, string key, int i, int *non_alpha_offset);
// Applies the cipher and manages ASCII offset
int apply_cipher(int character, int cipher, bool upper_case);

int main(int argc, string argv[])
{
    if (!args_valid(argc, argv[1]))
    {
        printf("You must provide a key string\n");
        exit(1);
    }

    string s = get_string("plaintext: ");
    string k = argv[argc - 1];
    // Used to skip non-alpha chars and keep track
    // of last used index of 'key'
    int non_alpha_offset = 0;

    for (int i = 0, s_l = strlen(s); i < s_l; i++)
    {
        s[i] = calc_cipher(s[i], k, i, &non_alpha_offset);
    }

    printf("ciphertext: %s\n", s);
}

bool args_valid(int argc, string key)
{
    if (argc != 2)
    {
        return false;
    }

    bool key_is_alpha = true;
    for (int i = 0, j = strlen(key); i < j; i++)
    {
        if (!isalpha(key[i]))
        {
            return key_is_alpha = false;
        }
    }

    return key_is_alpha;
}

int calc_cipher(int character, string key, int i, int *non_alpha_offset)
{
    // Used to compute the modulo to cycle the key
    int k_l = strlen(key);
    int ciph_char = character;
    char cipher = key[((i - *non_alpha_offset) % k_l)];
    if (isalpha(character))
    {
        ciph_char = apply_cipher(character, cipher, isupper(character));
    }
    else
    {
        *non_alpha_offset += 1;
    }

    return ciph_char;
}

int apply_cipher(int character, int cipher, bool upper_case)
{
    character += (tolower(cipher) - ASCII_OFFSET);
    if ((character > ASCII_LAST_UP) && upper_case)
    {
        character -= A_SIZE;
    }
    if (character > ASCII_LAST_LO)
    {
        character -= A_SIZE;
    }

    return character;
}
