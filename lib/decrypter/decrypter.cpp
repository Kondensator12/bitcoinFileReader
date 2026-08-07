// STD
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

#include "decrypter.h"



Decrypter::Decrypter(){}

std::vector<uint8_t> Decrypter::decryptXorEncryption(std::vector<uint8_t> encryptedData, std::vector<uint8_t> xorKey)
{
    if (xorKey.empty() || encryptedData.empty())
    {
        throw std::invalid_argument("Decrypter: Cotainer(s) is(are) empty.");
    }

    std::vector<uint8_t> decryptedData(encryptedData.size());

    const size_t keyLength = xorKey.size();

    for (size_t i = 0; i < encryptedData.size(); ++i)
    {
        decryptedData[i] = encryptedData[i] ^ xorKey[i % keyLength];
    }
    return decryptedData;
}
