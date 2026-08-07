/*! \file binFileReader.cpp
 *  Filled with functions for reading a bin file
 */

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <stdexcept>


#include "binFileReader.h"



BinFileReader::BinFileReader(const std::string& filename)
{
    //Create a file object (content of the file)
    this->file.open(filename, std::ios::binary);
}


bool BinFileReader::isOpen() const
{
    return file.is_open();
}


std::vector<uint8_t> BinFileReader::readFile()
{
    std::vector<uint8_t> fileData; //container for the content of the file. each vector entry is a byte.
    if (!file)
    {
        std::cout << "File was not opened. Check the file path and the access permissions" << std::endl;
        this->file.close();
    }
    if (file.eof())
    {
        std::cout << "The file is empty." << std::endl;
        this->file.close();
    }
    this->file.seekg(0, std::ios::end);// Change position in the file to the last character
    std::streamsize amountOfCharacters = this->file.tellg();// Change position in the file to the last character
    this->file.seekg(0, std::ios::beg);// return to the beginning of the file content

    try{
        fileData.resize(amountOfCharacters);/**< Create a vector with the reserved size*/
    }
    catch(...)
    {
        std::cout << "unknown error. Could not resize the vector to the Size of " << amountOfCharacters << std::endl;
        this->file.close();
    }

    if (this->file.read( reinterpret_cast<char*>(fileData.data()), amountOfCharacters))//reading the data
    {

        //DEBUG part // Makro
        #ifdef DEBUG

        std::cout << "The file was successfully read." << std::endl;
        std::cout << "File size: " << amountOfCharacters << " Bytes" << std::endl;

        //
        std::cout << "First Bytes:" << std::endl;// output of the first 16 bytes
        for (size_t i = 0; i < std::min<size_t>(16, fileData.size()); i++)
        {
            printf("%02X ", static_cast<unsigned char>(fileData[i]));
        }
        std::cout << std::endl;
        #endif
    }
    else
    {
        std::cout << "Reading of the file resulted an error." << std::endl;
        this->file.close();
    }
    this->file.close();

    return fileData;
}
