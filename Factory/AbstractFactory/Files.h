#include <string>

/**
 * @brief Abstraction for the File handlers. Simplifies the use of multiple different file handlers in tandem.
 */
class File
{
protected:
    std::string file_name;

public:
    File(std::string file) : file_name(file) {}
    // Extracts the data from the file.
    virtual void extract_data() = 0;
    virtual ~File() = default;
};

/**
 * @brief File handler for JSON files.
 */
class JsonFile : public File
{
public:
    JsonFile(std::string filename) : File(filename) {}

    void extract_data() override
    {
        std::cout << "Extracting Data from a " << file_name << "\n";
    }
};

/**
 * @brief File handler for CSV files.
 */
class CsvFile : public File
{
public:
    CsvFile(std::string filename) : File(filename) {}

    void extract_data() override
    {
        std::cout << "Extracting Data from a " << file_name << "\n";
    }
};