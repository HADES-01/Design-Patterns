#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Sentence
{
    struct WordToken
    {
        bool capitalize;
    };

    vector<string> words;
    map<int, WordToken> tokens;

    Sentence(const string &text)
    {
        istringstream iss{text};
        words = vector<string>(istream_iterator<string>{iss}, istream_iterator<string>{});
    }

    WordToken &operator[](size_t index)
    {
        tokens[index] = WordToken{};
        return tokens[index];
    }

    string str() const
    {
        vector<string> ws;
        for (size_t i = 0; i < words.size(); ++i)
        {
            string w = words[i];
            auto t = tokens.find(i);
            if (t != tokens.end() && t->second.capitalize)
            {
                // note: the annotation on ::toupper() below is only required
                // for GCC; other compilers work fine without it
                transform(w.begin(), w.end(), w.begin(), (int (&)(int))toupper);
            }
            ws.push_back(w);
        }

        ostringstream oss;
        for (size_t i = 0; i < ws.size(); ++i)
        {
            oss << ws[i];
            if (i + 1 != ws.size())
                oss << " ";
        }
        return oss.str();
    }
};
