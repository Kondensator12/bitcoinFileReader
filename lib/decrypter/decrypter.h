#pragma once
/**
 * @class Decrypt files
 */
class Decrypter
{
private:


public:
    /**
 * @brief class Decrypter. No definition parameters required
 */
    Decrypter();

    /**
 * @brief Uses Xor-key on the file vector to decrypt the content
 * @return std::vector<uint8_t> Vector with decrypted unsigned 8 bit integer entries
 */
    std::vector<uint8_t> decryptXorEncryption(std::vector<uint8_t> encryptedData, std::vector<uint8_t> xorKey);
};
