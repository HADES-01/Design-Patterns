/**
 * @cite Flyweight Pattern states that when a large number of similar objects have to be created then it is better to create that object only once which is shared across the objects that make use of it.
 * Aims at optimizing space complexity by creating similar objects only once.
 *
 * @brief Flyweight Pattern can be exemplified by a Sentence class that rather than storing the whole text together stores pointer to each word present in it. This saves space as their maybe a lot of repeating words.
 */

#include "boost\bimap.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef uint32_t key;

/**
 * @brief Monostate Word class that keeps track of all the unique words in a static `bimap`.
 *
 */
class Word
{
    // Stores all the words along with seed.
    static boost::bimap<key, std::string> words;
    // Keeps count of all the unique words seen.
    static key seed;

public:
    /**
     * @brief Get the word stored int the map at the given key.
     */
    static std::string get_word(key word_key)
    {
        return words.left.find(word_key)->second;
    }

    /**
     * @brief Stores the word in the map and returns the key.
     */
    static key add_word(std::string word)
    {
        auto word_key = words.right.find(word);
        if (word_key != words.right.end())
        {
            return word_key->second;
        }
        words.insert({++seed, word});
        return seed;
    }

    /**
     * @brief Get the current memory size by the map.
     */
    static int get_map_memory()
    {
        int res = 0;
        for (auto a : words)
        {
            res += a.right.size();
            res += sizeof(a.left);
        }
        return res;
    }
};

// Initialize the static members.
boost::bimap<key, std::string> Word::words = {};
key Word::seed = 0;

/**
 * @brief Sentence stores each word as a key in the words map.
 */
class Sentence
{
    std::vector<key> sentence_words;

public:
    /**
     * @brief Construct a new Sentence object from the given string sentence.
     */
    Sentence(std::string sentence)
    {
        std::istringstream iss(sentence);
        std::string token;

        while (std::getline(iss, token, ' '))
        {
            std::string lim;
            if (token.back() == '.' || token.back() == ',')
            {
                lim += token.back();
                token.pop_back();
            }
            sentence_words.push_back(Word::add_word(token));
            sentence_words.push_back(Word::add_word(lim));
        }
    }
    /**
     * @brief Resolves keys of the sentence to contruct the sentence string.
     */
    std::string get_sentence()
    {
        std::string res = "";
        for (auto a : sentence_words)
        {
            std::string word = Word::get_word(a);
            res += (word == "." || word == "," ? "" : " ");
            res += word;
        }
        if (res.size())
            res.erase(res.begin());
        return res;
    }
};

/**
 * @brief Collection of Sentences.
 */
class Book
{
    std::vector<Sentence> text;

public:
    /**
     * @brief Adds sentence string in to the book.
     */
    void add_Sentence(std::string sentence)
    {
        text.push_back(Sentence(sentence));
    }

    /**
     * @brief Get the book text as the string.
     */
    std::string get_text()
    {
        std::string res;
        for (auto a : text)
        {
            res += a.get_sentence();
        }
        return res;
    }
};

int main()
{
    Book b;
    std::string text = "";

    // Get sentences from the text file and add it to the Book.
    std::ifstream ifs("test.txt");
    std::string sentence;
    while (std::getline(ifs, sentence))
    {
        b.add_Sentence(sentence);
        text += sentence;
    }

    ifs.close();
    // ! Size of the raw text is much larger than the size taken by the word_map.
    std::cout << "Memory taken by the text :: " << text.size() << " bytes.\n";
    std::cout << "Memory taken by the Flyweight text :: " << Word::get_map_memory() << " bytes.\n";

    return 0;
}