#pragma once
#include <vector>
#include <string>

class BitcoinBlockContainer{

private:

    struct BlockHeader
    {
        std::string  version;
        std::string  previousHash;
        std::string  merkleRoot;
        std::string  timestamp;
        std::string  bits;
        std::string  nonce;
    };

    struct TxOutput
    {
        std::string value;
        std::string scriptPubKey;
    };


    struct TxInput
    {
        std::string  prevTxHash;
        std::string  outputIndex;
        std::string  scriptSig;
        std::string  sequence;
    };

    struct Transaction
    {
        std::string  version;
        std::vector<TxInput> inputs;
        std::vector<TxOutput> outputs;
        std::string  lockTime;
    };


    struct Block
    {
        std::string magic;
        bool magicFound;
        std::string blockSize;
        BlockHeader header;
        std::vector<Transaction> transactions;
    } ;


public:
    BitcoinBlockContainer();

    Block bitcoinBlock;

    BlockHeader bitcoinBlockHeader;

    Transaction bitcoinTransaction;

};
