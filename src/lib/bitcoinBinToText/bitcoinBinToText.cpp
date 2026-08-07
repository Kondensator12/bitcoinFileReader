// STD
#include "bitcoinBinToText.h"
#include <sstream>
#include <ctime>
#include <iostream>
#include <algorithm>


/*Information:
  Magic                Hex
  Block Size          Dec
  Version             Dec
  Previous Hash       Hex (reversed)
  Merkle Root         Hex (reversed)
  Timestamp       	Date
  Bits            	Hex
  Nonce               Hex or Dec
  */
/*
   4 Byte   Version        (uint32 little endian)
   32 Byte  Previous Hash  (byte order reversed for display)
   32 Byte  Merkle Root    (byte order reversed for display)
   4 Byte   Timestamp      (uint32 little endian)
   4 Byte   Bits           (uint32 little endian)
   4 Byte   Nonce          (uint32 little endian)
   */

BitcoinBinToText::BitcoinBinToText(std::vector<uint8_t> decryptedBlockFileDataVector)
{
	this->blockFileDataVector=decryptedBlockFileDataVector;
}

std::vector<BitcoinBlockContainer> BitcoinBinToText::readBlocks()
{
	// ich fange mit 0 an
	this->position=0;

	//Rückgabe-Container
	std::vector<BitcoinBlockContainer> blockVektor;


	//Container für die Daten
	BitcoinBlockContainer bitcoinBlockContainerObject;
	//----------Block-----------------------------------------------------------------------
	//Read Magic Bytes
	bitcoinBlockContainerObject.bitcoinBlock.magic= readBytes(4, false);
	std::cout<<"Magic Bytes: " <<bitcoinBlockContainerObject.bitcoinBlock.magic<<std::endl;




	//----------Magic Bytes can differ, depending on the network.
	if (!checkMagicBytes(bitcoinBlockContainerObject))
	{
		std::cout << "Could not detect magic bytes. Please check the network and the corresponding magic bytes otherwise check if the file is a bitcoin block file" << std::endl;
	}
	//Block Size
	bitcoinBlockContainerObject.bitcoinBlock.blockSize=std::to_string(readInteger(4, true));
	//70
	std::cout<<"Block Size: " <<bitcoinBlockContainerObject.bitcoinBlock.blockSize<<std::endl;

	//Validate Block Size
	size_t nextBlockPosition = 8 + std::stoi(bitcoinBlockContainerObject.bitcoinBlock.blockSize);

	std::cout
		<< "Next magic: ";

	for(size_t i = nextBlockPosition; i < nextBlockPosition + 4; i++)
	{
		std::cout
			<< std::hex
			<< std::setw(2)
			<< std::setfill('0')
			<< (int)blockFileDataVector[i];
	}

	std::cout << std::endl;

	//----------Block-------------------
	//----------Header-------------------
	//Version
	bitcoinBlockContainerObject.bitcoinBlockHeader.version= std::to_string(readInteger(4, true));
	std::cout<<"block version: " <<bitcoinBlockContainerObject.bitcoinBlockHeader.version<<std::endl;

	//Previous Hash
	bitcoinBlockContainerObject.bitcoinBlockHeader.previousHash=readBytes(32, true);

	std::cout<<"Previous block hash: "<<bitcoinBlockContainerObject.bitcoinBlockHeader.previousHash<<std::endl;


	//Merkle root
	bitcoinBlockContainerObject.bitcoinBlockHeader.merkleRoot=readBytes(32, true);
	std::cout<<"block merkle root: " <<bitcoinBlockContainerObject.bitcoinBlockHeader.merkleRoot<<std::endl;


	bitcoinBlockContainerObject.bitcoinBlockHeader.timestamp=timeStamp();
	std::cout<<"block time stamp: " <<bitcoinBlockContainerObject.bitcoinBlockHeader.timestamp<<std::endl;

	bitcoinBlockContainerObject.bitcoinBlockHeader.bits= readBytes(4, false);
	std::cout<<"block bits: " <<bitcoinBlockContainerObject.bitcoinBlockHeader.bits<<std::endl;

	bitcoinBlockContainerObject.bitcoinBlockHeader.nonce=readBytes(4, false);
	std::cout<<"block nounce: " <<bitcoinBlockContainerObject.bitcoinBlockHeader.nonce<<std::endl;






	//----------Header-------------------
	//----------------------}-----------------------------------------------------------------------------------------------------------------------------------------------
	return blockVektor;
	}



std::string BitcoinBinToText::readBytes(size_t count, bool littleEndian)
{
	std::ostringstream ss;

	if (littleEndian)
	{
		for (int i = static_cast<int>(count) - 1; i >= 0; --i)
		{
			ss << std::hex
				<< std::setw(2)
				<< std::setfill('0')
				<< static_cast<int>(blockFileDataVector[position + i]);
		}
	}
	else
	{
		for (size_t i = 0; i < count; ++i)
		{
			ss << std::hex
				<< std::setw(2)
				<< std::setfill('0')
				<< static_cast<int>(blockFileDataVector[position + i]);
		}
	}

	position += count;
	return ss.str();
}

bool BitcoinBinToText::checkMagicBytes(BitcoinBlockContainer bitcoinBlockContainerObject)
{
	std::vector<std::string> networks;
	networks={"f9beb4d9","0b110907","fabfb5da","dab5bffa"};

	for (auto network:networks)
	{
		if (bitcoinBlockContainerObject.bitcoinBlock.magic==network)
		{
			return true;
		}
	}
	return false;
}

std::string BitcoinBinToText::timeStamp()
{
	uint32_t value =
		static_cast<uint32_t>(blockFileDataVector[position])
		| (static_cast<uint32_t>(blockFileDataVector[position+1]) << 8)
		| (static_cast<uint32_t>(blockFileDataVector[position+2]) << 16)
		| (static_cast<uint32_t>(blockFileDataVector[position+3]) << 24);

	position += 4;

	std::time_t t = value;

	std::string result = std::ctime(&t);

	if (!result.empty() && result.back() == '\n')
	{
		result.pop_back();
	}
	return result;
}

uint64_t BitcoinBinToText::readInteger(size_t count, bool littleEndian)
{
	uint64_t value = 0;

	if(littleEndian)
	{
		for(size_t i = 0; i < count; i++)
		{
			value |= static_cast<uint64_t>(
					blockFileDataVector[position+i]
					) << (8*i);
		}
	}

	position += count;

	return value;
}
