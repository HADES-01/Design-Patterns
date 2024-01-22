/**
 * @cite Interface Segregation Principle states that a class shouldn't be force to implement features that it doesn't use.
 * Aims at promoting Flexibility and Meaningfullness as no object will be forced to implement functions that are useless.
 *
 * @brief Interface Segreagation Principle can be exemplified by FileProcessor interface that assumes that all File Processors must be able to read, write and print the file.
 * What happens the client only needs a read-only or write-only File Processor?
 * What happens when a useless function (like wite() from a read-only class) is called from the object ?
 */

#include <iostream>
#include <vector>
/**
 * @brief Interface for a File Processor that assumes all File Processors can read, write and print.
 */
class IFileProcessor
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
    virtual void print() = 0;
};

/**
 * @brief Text File works with the IFileProcessor interface as a text file can be read, written to and printed.
 */
class TextFile : public IFileProcessor
{
public:
    void read()
    {
        std::cout << "Reading Text File!!!\n";
    }
    void write()
    {
        std::cout << "Writing to Text File!!!\n";
    }
    void print()
    {
        std::cout << "Printing Text File!!!\n";
    }
};

/**
 * @brief System File can't work with IFileProcessor interface as a system file can only be read and can neither be written to nor be printed.
 *
 * ! @warning SystemFile has to implement useless features of write() and print() that results in error
 */
class SystemFile : public IFileProcessor
{
public:
    void read()
    {
        std::cout << "Reading!!!\n";
    }
    void write()
    {
        throw std::runtime_error("System Files are read-only");
    }
    void print()
    {
        throw std::runtime_error("System Files are read-only");
    }
};

/**
 * @brief Segregated Interface that only implements reading functionality.
 */
class IReadProcessor
{
public:
    virtual void read() = 0;
};

/**
 * @brief Segregated Interface that only implements writing functionality.
 */
class IWriteProcessor
{
public:
    virtual void write() = 0;
};

/**
 * @brief Segregated Interface that only implements printing functionality.
 */
class IPrintProcessor
{
public:
    virtual void print() = 0;
};

/**
 * @brief Word File implements functionalities from IReadProcessor, IWriteProcessor and IPrintProcessor as a word file can be read, written to and be printed.
 */
class WordFile : public IReadProcessor, public IWriteProcessor, public IPrintProcessor
{
public:
    void read()
    {
        std::cout << "Reading Word File!!!\n";
    }
    void write()
    {
        std::cout << "Writing to Word File!!!\n";
    }
    void print()
    {
        std::cout << "Printing Word File!!!\n";
    }
};

/**
 * @brief Video File implements functionalitie only from IReadProcessor and IWriteProcessor as it can only be read and maybe written to but can definitely not be printed.
 */
class VideoFile : public IReadProcessor, public IWriteProcessor
{
public:
    void read()
    {
        std::cout << "Reading Video File!!!\n";
    }
    void write()
    {
        std::cout << "Writing to Video File!!!\n";
    }
};

/**
 * @brief API that consumes IFileProcessors and tries to write to them
 */
void write_to_IFileProcessors(std::vector<IFileProcessor *> files)
{
    for (auto file : files)
        file->write();
}

/**
 * @brief API that consumes IWriteProcessors and tries to write to them
 */
void write_to_IWriteProcessors(std::vector<IWriteProcessor *> files)
{
    for (auto file : files)
        file->write();
}

int main()
{
    try
    {
        // ! Writing to SystemFile result in an error and may break functionailty.
        TextFile *text = new TextFile;
        SystemFile *system = new SystemFile;
        write_to_IFileProcessors({text, system});
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR :: " << e.what() << '\n';
    }

    WordFile *word = new WordFile;
    VideoFile *video = new VideoFile;

    write_to_IWriteProcessors({word, video});
    return 0;
}
