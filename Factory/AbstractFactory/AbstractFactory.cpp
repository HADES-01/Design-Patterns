/**
 * @cite Abstract Factory Pattern states that if the objects being intialized are implementation of some abstract class then their corresponding factories should also have a Abstract Factory that they implement.
 * The abstract factory makes the intialization independent from the type of the object.
 * Aims at increasing extensibility by providing a highly modular API.
 *
 * @brief Abstract Factory Pattern can be exemplified by an Extractor class that can extract data from different file formats (like json, csv etc.).
 */

#include "iostream"
#include "map"
#include "FileFactory.h"

/**
 * @brief Extractor makes use of the different File Factories in order to instantiate different File handlers.
 */
class Extractor
{
    // stores the supported file formats and their corresponding factories.
    std::map<std::string, FileFactory*> file_factories; 
public:

    Extractor() {
        // Initialize all the factories
        file_factories["json"] = new JsonFileFactory();
        file_factories["csv"] = new CsvFileFactory();
    }

    /**
     * @brief Takes the filename and instantiates the File object based on the extension.
     */
    File* extract(std::string filename) {
        auto ext = filename.substr(filename.find_last_of('.')+1);
        if(!file_factories[ext]) {
            throw std::runtime_error("Extension ." + ext + " not recognized .. ");
        }
        auto file = file_factories[ext]->make(filename);
        return file;
    }
};

int main() {
    // Highly simplified API that takes only the filename and returns the required File.
    Extractor extractor;
    
    // CSV file loaded 
    auto csv = extractor.extract("data.csv");
    csv->extract_data();

    // JSON file loaded
    auto json = extractor.extract("data.json");
    json->extract_data();
    
    return 0;
}