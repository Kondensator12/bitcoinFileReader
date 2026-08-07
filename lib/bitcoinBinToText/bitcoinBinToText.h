#pragma once
#include<iomanip>
#include <vector>
#include <cstdint>
#include <cstring>
#include "bitcoinBlockContainer.h"

/**
 * @class Converts bitcoin binary content to a string
 */
class BitcoinBinToText
{
private:
    /**
 * @brief stores the origin data
 */
    std::vector<uint8_t> blockFileDataVector;

    /**
 * @brief vector entry position of the blockFileDataVector
 */
    int position;



public:
    /**
 * @brief class constructor
 * explicit : the data vector is not optional. one data vector = one class object
 */
    explicit BitcoinBinToText(std::vector<uint8_t> decryptedBlockFileDataVector);

    /**
 * @brief Main function which transform the binary data into string type data
 */
    std::vector<BitcoinBlockContainer> readBlocks();

    /**
 * @brief Reads custome amount of bytes
 */
    std::string readBytes(size_t count, bool littleEndian);

    /**
 * @brief Checks if magic bytes are valid
 */
    bool checkMagicBytes(BitcoinBlockContainer bitcoinBlockContainerObject);

    /**
 * @brief reads the time binary data and converts it to a time stamp
 */
    std::string timeStamp();

    /**
 * @brief reads the time binary data and converts it to a time stamp
 */
    uint64_t readInteger(size_t count, bool littleEndian);

};
