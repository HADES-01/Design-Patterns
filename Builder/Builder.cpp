/**
 * @cite Builder Pattern states that when a complex object has to be constructed instead of providing a constructor that takes all configurations as arguments you can provide a step-by-step API for that same object creation.
 * - Aims at promoting Code Readability and Manageability as object creation is broken down into multiple steps.
 * - Builder Pattern is a type of Piecewise Creational Patterns.
 * - Builder Pattern can have fluent builders that allow users to chain the build commands together like 'builder.do_this().do_that()'
 *
 * @brief Builder Pattern can be exemplified by trying to create HTML elements programmatically.
 * One approach is to just start creating a string and appending opening tag, children and closing tags to it.
 *  - But, what happens when we need to add another child to it later on ?
 *  - Also, what happens when we need to add nested children?
 *
 * Another and a more Object-oriented approach is to create a HtmlBuilder class that takes the name of the element to be created (e.g. ul, p) and provides a simple API for adding children to it.
 */
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>

// Forward declaration of UlBuilder to get access in HtmlElement class
class UlBuilder;
/**
 * @brief HtmlElement class is an entity representation of HTML elements. Contains tag_name, innerText, children etc.
 * This is an inner class i.e client cannot directly create an object of it and to make sure that client cannot create a HtmlElement, we can make the contructors private.
 * 
 * @param `str()` returns HTML element in string along with all of its children in correct format.
 * @param `build()` static function that builds the HtmlElement using the HtmlBuilder
 */
class HtmlElement
{
    std::string tagName, innerText;
    std::vector<HtmlElement> children;
    int indentSize = 2;
    HtmlElement(std::string name, std::string value): tagName(name), innerText(value) {}
    void addChildren(HtmlElement el)
    {
        children.emplace_back(el);
    }

public:
    std::string str(int indent = 0) const
    {
        std::ostringstream element_oss;
        std::string indent_string(indent * indentSize, ' ');
        element_oss << indent_string << "<" << tagName << ">\n";
        if (innerText.size() > 0)
            element_oss << indent_string << indent_string << innerText << "\n";

        for (auto child : children)
        {
            element_oss << child.str(indent + 1);
        }

        element_oss << indent_string << "</" << tagName << ">\n";

        return element_oss.str();
    }


    friend class UlBuilder;
    friend class LiBuilder;

    /**
     * @brief Providing the API to create `HtmlElement` only through `HtmlBuilder`
     * 
     * @return `std::unique_ptr<UlBuilder>`
     */
    static std::unique_ptr<UlBuilder> build_ul() {
        return std::make_unique<UlBuilder>();
    }
};

/**
 * @brief Builder class for <li> tag that provides a step-by-step API for client to create <li> tags. 
 */
class LiBuilder {
    HtmlElement root;
public:
    LiBuilder(std::string innerText = ""):root("li", innerText) {}

    // Make the Builder fluent by returning the refrence of current object
    LiBuilder& add_children(std::string tagName, std::string innerText) {
        root.addChildren(HtmlElement(tagName, innerText));
        return *this;
    }

    std::string str() const {
        return root.str();
    }

    operator HtmlElement() const {
        return root;
    }

    friend class UlBuilder;
};

/**
 * @brief Builder class for <ul> tag that provides a step-by-step API for client to create <ul> tags. 
 */
class UlBuilder {
    HtmlElement root;
public:
    UlBuilder(): root("ul", "") {}

    UlBuilder& add_li(std::string list_item) {
        root.addChildren(HtmlElement("li", list_item));
        return *this;
    }

    UlBuilder& add_li(LiBuilder &li) {
        root.addChildren(li.root);
        return *this;
    }

    std::string str() const {
        return root.str();
    }

    operator HtmlElement() const {
        return root;
    }
};

// Change this to output elements to terminal
bool to_html_file = true;
std::ofstream ofs("ul.html");

void print(std::string text) {
    if(to_html_file) ofs << text << "\n\n\n";
    else std::cout << text;
}

/**
 * @brief Trying to replicate a <ul> tag with 3 child <li> tags appended to it with both the above mentioned approaches.
 */
int main()
{
    std::vector<std::string> original_items{"Apple", "Orange", "Pear"};
    std::string new_item = "Banana";

    // Using first Approach to use just the string representation.
    std::ostringstream oss;
    oss << "<ul>\n";
    for (auto a : original_items)
    {
        oss << "  <li>" + a + "</li>\n";
    }
    oss << "</ul>\n";
    print(oss.str());

    // ! Adding another child to it can get very tedious after a certain point.
    long long size_ul = 6;
    oss.seekp(oss.tellp() - size_ul);
    oss << "  <li>" + new_item + "</li>\n";
    oss << "</ul>\n";
    print(oss.str());

    // !adding nested elements is nearly impossible without reconstructing the entire string.


    // Using second approach and creating element piecewise using UlBuilder
    UlBuilder ul;
    for(auto item:original_items) ul.add_li(item);
    print(ul.str());

    // Adding another child to it is also much simpler 
    ul.add_li(new_item);
    print(ul.str());

    // Adding nested elements to it also much simpler
    LiBuilder li("Grapes");
    li.add_children("p", "Grapes are the best !!!");
    ul.add_li(li);

    print(ul.str());

    // Example of fluent builder pattern
    auto ul_fluent = UlBuilder().add_li("Orange").add_li("Grapes").add_li("Apple");
    print(ul_fluent.str());

    // Building HTMLelements using HtmlElement::build()
    auto ul_build = HtmlElement::build_ul()->add_li("Hello").add_li("World");
    print(ul_build.str());

    std::cout << "Written All elements to \'ul.html\'";
    return 0;
}