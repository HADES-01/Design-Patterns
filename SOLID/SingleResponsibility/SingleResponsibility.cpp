/**
 * @cite Single Responsibility princliple states that each entity (class, function, structs, etc.) in the code should have one and only one concern or responsibilty.
 * Aims at increasing modularity by making each entity as independent as possible.
 *
 * @brief Single Responsibilty principle exemplified by creating a journal entity that manages entires inside a journal. 
 * What happens when we need to add the saving to physical storage functionality to this entity? 
 * What if that functionality requires modification in the future (let's say from physical storage to a database)?
 */

#include <vector>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

/**
 * @brief General Journal class that has only one concern of managing entries.
 */
class Journal
{
protected:
    std::string title;
    std::vector<std::string> entries;

public:
    Journal(const std::string &title) : title(title) {}

    void add_entry(std::string entry)
    {
        entries.push_back(
            boost::lexical_cast<std::string>(entries.size() + 1) + ": " + entry);
    }

    /**
     * @brief saves the journal and its entries to physical storage
     *
     * @warning
     * ! save_journal Function adds another concern to the Journal Class that has to be taken care of when extending its functionality to children classes.
     *
     * ! What if the method of storage was changed? Essentially the every extension of Journal will have to be changed to accomodate the new functionality
     */
    void save_journal(std::string filename)
    {
        std::ofstream ofs(filename);
        ofs << title << std::endl;
        for (auto entry : entries)
        {
            ofs << entry << std::endl;
        }
    }

    friend class PersistenceManager;
};

/**
 * @brief Specialized version of Journal class that also stores the name of the person adding the entry as well as the company name.
 */
class WorkJournal : Journal
{
    std::string companyName;

public:
    WorkJournal(std::string title, std::string companyName) : Journal(title), companyName(companyName) {}

    void add_entry(std::string entry, std::string author)
    {
        entries.push_back(
            boost::lexical_cast<std::string>(entries.size() + 1) + ": " + entry + " - " + author);
    }

    /**
     * @brief save_journal saves the work journals to the physical storage along with the company name.
     *
     * @warning
     * ! Whenever the implementation of saving mechanism changes this will have to be changed as well as it is an extension of Journal
     */
    void save_journal(std::string filename)
    {
        std::ofstream ofs(filename);
        ofs << title << " - " << companyName << std::endl;
        for (auto entry : entries)
        {
            ofs << entry << std::endl;
        }
    }

    friend class PersistenceManager;
};

/**
 * @brief Persistence Manager class which is only concerned with saving the journals to physical storage.
 * @details
 * * Only this class will have to be changed if the implementation of saving mechanism changes.
 */
class PersistenceManager
{
public:
    /**
     * @brief saves the journal and its entries to physical storage
     */
    static void save_journal(Journal &journal, std::string filename)
    {
        std::ofstream ofs(filename);
        ofs << journal.title << std::endl;
        for (auto entry : journal.entries)
        {
            ofs << entry << std::endl;
        }
    }
    /**
     * @brief save_journal saves the work journals to the physical storage along with the company name.
     */
    static void save_journal(WorkJournal &journal, std::string filename)
    {
        std::ofstream ofs(filename);
        ofs << journal.title << " - " << journal.companyName << std::endl;
        for (auto entry : journal.entries)
        {
            ofs << entry << std::endl;
        }
    }
};

int main()
{
    Journal diary("Dear Diary");
    diary.add_entry("I started learning Design Patterns.");
    diary.add_entry("Single Responsibilty principle seems gay.");

    diary.save_journal("dear_diary.txt");
    PersistenceManager::save_journal(diary, "dear_diary.txt");

    WorkJournal notes("Work Notes", "ABC inc.");
    notes.add_entry("Perform Sanity Checks on Database.", "George");
    notes.add_entry("Tell Joe to learn Design Pattern.", "Helen");

    notes.save_journal("work_notes.txt");
    PersistenceManager::save_journal(notes, "work_notes.txt");

    return 0;
}