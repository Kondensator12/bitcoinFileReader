#pragma once

/**
 * @class Binary file read class
 */
class BinFileReader
{
private:
    /**
 * @brief file stream of the object which should contain the whole file information
 */
    std::ifstream file;

public:


    /**
 * @brief class constructor
 * explicit : the file path is not optional. one file = one class object
 */
    explicit BinFileReader(const std::string& filePath);

    /**
 * @brief checks if the file was successfully opened
 * @return true if the file was opened else false
 */
    bool isOpen() const;

    /**
 * @brief reads the content of a binary file into a vector. The entries consist of unsigned 8 bit integer.
 * -This function uses a fstream to read the content of the file.
 *  You get an error output if
 *      -File was not successfully opened
 *      -File is empty
 *      -Reading was not successfull
 * @return std::vector<uint8_t> Vector with unsigned 8 bit integer entries
 * @usage
 * BinFileReader binFileReaderObject(pathOfTheFile);
 * std::vector<uint8_t> fileData=binFileReaderObject.readFile();
 */
    std::vector<uint8_t> readFile();

};
