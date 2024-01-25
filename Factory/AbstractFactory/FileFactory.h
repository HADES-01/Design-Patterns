#include "Files.h"

/**
 * @brief Abstract File Factory that simplifies the creation of differents File handlers.
 */
class FileFactory
{
public:
    // Instantiates the required File handler.
    virtual File *make(std::string filename) = 0;
    virtual ~FileFactory() = default;
};

/**
 * @brief File Factory for JSON file handler.
 */
class JsonFileFactory : public FileFactory
{
public:
    File *make(std::string filename) override
    {
        std::cout << "Making a Json File Handler ... \n";
        return new JsonFile(filename);
    }
};


/**
 * @brief File Factory for CSV file handler.
 */
class CsvFileFactory : public FileFactory
{
public:
    File *make(std::string filename) override
    {
        std::cout << "Making a Csv File Handler ... \n";
        return new CsvFile(filename);
    }
};