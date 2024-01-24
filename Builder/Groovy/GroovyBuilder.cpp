/**
 * @cite Groovy-Style Builder allows user to create objects of a Domain-Specific Language interpretation in the form of nested object intitialization. It uses the c++ feature of uniform initiailization to achieve this.
 * Known as Groovy-Style builder because the creation of DSL was groovy only thing before.
 * Intialization looks like `A{ B{ }, C{ D{ "Hello" } } }`
 * 
 * @brief Groovy Style Builders can be exemplified by creating a DSL for HTML.
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

/**
 * @brief Imitates basic <tag></tag> in html. Can have children, attributes as well innerText.
 */
class HtmlTag
{
protected:
  std::string tag_name, innerText;
  std::vector<HtmlTag> children;
  std::vector<std::pair<std::string, std::string>> attributes;
  /**
   * @brief Construct a new Html Tag object with the required tag_name.
   * Constructor is protected so that only Derived classes can make the object.
   *
   * @param tag name of the tag.
   * @param innerText OPTIONAL - `innerText` of the tag
   * @param children OPTIONAL - `HtmlTag` children of the tag
   * @param attrs OPTION - pairs of attributes of the tag.
   */
  HtmlTag(std::string tag, std::string innerText = "", std::initializer_list<HtmlTag> children = {}, std::initializer_list<std::pair<std::string, std::string>> attrs = {}) : tag_name(tag), innerText(innerText), children(children), attributes(attrs) {}

public:
  std::string str(int indent = 0)
  {
    std::ostringstream os;
    std::string indent_str(indent, '\t');
    os << indent_str << "<" + tag_name;
    if (attributes.size() == 0 && children.size() == 0 && innerText == "")
    {
      os << "/>\n";
      return os.str();
    }

    for (auto attr : attributes)
    {
      os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    if (children.size() == 0 && innerText == "")
    {
      os << "/>\n";
      return os.str();
    }
    else
      os << ">\n";

    os << std::string(indent+1, '\t') << innerText << "\n";
    for (auto child : children)
    {
      os << child.str(indent + 1);
    }
    os << indent_str << "</" + tag_name + ">\n";
    return os.str();
  }

  friend std::ostream &operator<<(std::ostream &os, HtmlTag &&tag)
  {
    os << tag.str();
    return os;
  }
};

/**
 * @brief Imitate <p> tag. Can have children, attributes as well as innerText
 */
class P : public HtmlTag
{
public:
  P() : HtmlTag("p") {}
  P(std::string innerText, std::initializer_list<HtmlTag> children) : HtmlTag("p", innerText, children) {}
  P(std::initializer_list<HtmlTag> children) : HtmlTag("p", "", children) {}
};

/**
 * @brief imitiates <img> tag. Only contains attributes.
 */
class IMG : public HtmlTag
{
public:
  IMG(std::string src) : HtmlTag("img", "", {}, {{"src", src}}) {}
};

int main()
{
  // Groovy-style initialization i.e nested initialization
  std::cout << P{"Pika Pika !!!",{
                   IMG{"http://pokemon.com/pikachu.png"},
                   P{
                       IMG{"http://pokemon.com/pikachu.png"},
                   }}}
            << std::endl;

  return 0;
}