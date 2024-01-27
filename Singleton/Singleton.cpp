/**
 * @cite Singleton Pattern states that when constructing an object is expensive then that class should only have a single instance available which should then be used throughout the program.
 *
 * @brief Singleton Pattern can be exemplified by a Database Class that loads up the database only once and provides an API to interact with it.
 * What happens when we need data from the database to actually test the Singleton Database Class?
 */

#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <vector>

/**
 * @brief Interface for Database classes.
 */
class AbstractDatabase
{
public:
    virtual int get_population(const std::string &country) = 0;
};

/**
 * @brief Database class that loads up database and provides API to interact with it.
 */
class Database : public AbstractDatabase
{

    std::map<std::string, int> populations;

    /**
     * @brief Contructor is private so that no instantiation is done on the client-side.
     */
    Database()
    {
        std::cout << "Loading Database ...\n";
        std::ifstream ifs("db.csv");
        std::string line;
        while (std::getline(ifs, line))
        {
            std::string country = line.substr(0, line.find_first_of(','));
            std::string population = line.substr(line.find_first_of(',') + 1, line.size());
            populations[country] = std::stoi(population);
        }
    }

public:
    // Deleted Copy contructor and equal operator to avoid instatiation by copying.
    Database(Database &) = delete;
    void operator=(Database &) = delete;

    // Returns a static database reference.
    static Database &get()
    {
        static Database db;
        return db;
    }

    // Returns Population (in miliions) for a counrty.
    int get_population(const std::string &country)
    {
        return populations[country];
    }
};

/**
 * @brief RecordFinder class that finds records on the actual Database.
 * !@warning Highly Coupled with Databse class.
 */
class RecordFinder
{
public:
    int total_population(std::vector<std::string> countries)
    {
        int res = 0;
        for (auto country : countries)
        {
            res += Database::get().get_population(country);
        }
        return res;
    }
};

/**
 * !@warning Unit testing of RecordFinder becomes integration testing as RecordFinder is highly coupled with Database class.
 */
TEST(TotalPopulationTests, RecordFinderTest)
{
    RecordFinder rf;

    // ! Has to be hard coded using the values from the actual databse making the test inextensible.
    std::vector<std::string> countries = {"India", "China"};

    // ! Has to be hard coded using the values from the actual databse making the test inextensible.
    EXPECT_EQ(rf.total_population(countries), 1438 + 1380);
}

/**
 * @brief Dummy Database that allows the unit testing of RecordFinder class.
 * Acts a dependency injection to decouple RecordFinder and Database class.
 */
class DummyDatabase : public AbstractDatabase
{
    std::map<std::string, int> dummy;

public:
    DummyDatabase()
    {
        dummy["dummy1"] = 1;
        dummy["dummy2"] = 4;
        dummy["dummy3"] = 3;
    }
    int get_population(const std::string &key)
    {
        return dummy[key];
    }
};

/**
 * @brief BetterRecordFinder class that finds records on the database provided rather than the actual Database. 
 * Unlike RecordFinder, it is Decoupled from the Database class.
 */
class BetterRecordFinder
{
    AbstractDatabase &db;

public:
    explicit BetterRecordFinder(AbstractDatabase &db): db{db} {}

    int total_population(std::vector<std::string> countries)
    {
        int res = 0;
        for (auto country : countries)
        {
            res += db.get_population(country);
        }
        return res;
    }
};

/**
 * Unit Testing of BetterRecordFinder is possible because it is not coupled with Database class.
 */
TEST(TotalPopulationTests, BetterRecordFinderTest)
{
    DummyDatabase db{};
    BetterRecordFinder rf(db);

    // Values are taken from the dummy database created internally making the test extensible.
    std::vector<std::string> keys = {"dummy1", "dummy2"};
    EXPECT_EQ(rf.total_population(keys), 5);
}

int main(int argc, char *argv[])
{
    // Getting the reference of the singleton object.
    auto db = &(Database::get());

    std::string country = "India";
    std::cout << "Population of " << country << " is " << db->get_population(country) << " million\n";

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // return 0;
}