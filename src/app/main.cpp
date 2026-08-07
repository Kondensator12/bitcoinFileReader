#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <cstdint>

#include "decrypter.h"
#include "bitcoinBinToText.h"
#include "binFileReader.h"


//param 1: blk file
//param 2: xor file
int main(int argc, char *argv[])
{
    //std::string pfad1="/home/kondensator/projects/bitCoinDataReader/testData/blk00050.dat";
    //std::string pfad2="/home/kondensator/projects/bitCoinDataReader/testData/xor.dat";

    std::cout<<"Number of given parameters(1 is program name): " << argc<<std::endl;
    BinFileReader binBlockFileReaderObject(argv[1]);
   // BinFileReader binBlockFileReaderObject(pfad1);

    // Read the blk-file
    //uint8_t -> 8Bits (1 byte) 2**8=256 oder in bit-Darstellung: 0000 0000
    std::vector<uint8_t> blockfileData=binBlockFileReaderObject.readFile();

    BinFileReader xorBinFileReaderObject(argv[2]);
    //BinFileReader xorBinFileReaderObject(pfad2);

    // Read the xor-file
    std::vector<uint8_t> xorKeyData=xorBinFileReaderObject.readFile();

    Decrypter decrypterObject;
    std::vector<uint8_t> decryptedBlockFileDataVector=decrypterObject.decryptXorEncryption(blockfileData, xorKeyData);

    //Transform to Text
    BitcoinBinToText bitcoinToTextObject(decryptedBlockFileDataVector);

    //TO-DO
    //Read Transactions
    //Read TxIns and TxOuts
    //Check block version differences
    //Save all block in a vector

    std::vector<BitcoinBlockContainer> BitcoinBlockContainerVector=bitcoinToTextObject.readBlocks();

}
