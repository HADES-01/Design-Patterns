#include <string>
#include <vector>
#include <ostream>
using namespace std;

struct Field
{
    string name, type;

    Field(const string &name, const string &type) : name{name}, type{type} {}

    friend ostream &operator<<(ostream &os, const Field &obj)
    {
        return os << obj.type << " " << obj.name << ";";
    }
};

struct Class
{
    string name;
    vector<Field> fields;

    friend ostream &operator<<(ostream &os, const Class &obj)
    {
        os << "class " << obj.name << "\n{\n";
        for (auto &&field : obj.fields)
        {
            os << "  " << field << "\n";
        }
        return os << "};\n";
    }
};

class CodeBuilder
{
    Class the_class;

public:
    CodeBuilder(const string &class_name)
    {
        the_class.name = class_name;
    }

    CodeBuilder &add_field(const string &name, const string &type)
    {
        the_class.fields.emplace_back(Field{name, type});
        return *this;
    }

    friend ostream &operator<<(ostream &os, const CodeBuilder &obj)
    {
        return os << obj.the_class;
    }
};