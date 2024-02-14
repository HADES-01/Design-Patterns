/**
 * @cite Memento Pattern states that inorder to capture and restore system state, the state of the system should be stored as an object(memento), which can then be replaced with the current state.
 * Aims at making operations reversible and allowing the rollback functionalities.
 *
 * @brief Memento Pattern can be exemplified by a Text Editor where you can undo and redo the changes done to the text.
 */

#include <memory>
#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Stores all the intermediate states of the TextEditor.
 */
class TextMemento
{
    std::string text;

public:
    TextMemento(std::string state) : text(state) {}
    friend class TextEditor;
};

/**
 * @brief Text Editor that provides undo and redo functionality by storing the intermediate changes and states.
 */
class TextEditor
{
    // Actual data that is changing.
    std::string text;
    // Refers to all the changes made so far.
    std::vector<std::shared_ptr<TextMemento>> changes;
    // refers to the index into the chages vector.
    int current;

public:
    TextEditor(std::string text) : text(text)
    {
        changes.emplace_back(std::make_shared<TextMemento>(text));
        current = 0;
    }

    /**
     * @brief Adds another word to the string.
     */
    void add_word(std::string word)
    {
        text += word;
        changes.emplace_back(std::make_shared<TextMemento>(text));
        current++;
    }

    // Restores the text to some previous stored state.
    void restore(std::shared_ptr<TextMemento> memento)
    {
        if (!memento)
            return;
        text = memento->text;
        changes.push_back(memento);
        current = changes.size() - 1;
    }

    // Undos a command performed i.e. rolls back one change.
    void undo()
    {
        if (current == 0)
            return;
        current--;
        text = changes[current]->text;
    }

    // Redos a command that was previously undone.
    void redo()
    {
        if (current + 1 == changes.size())
            return;
        current++;
        text = changes[current]->text;
    }

    friend std::ostream &operator<<(std::ostream &os, const TextEditor &te)
    {
        return os << "Text : " << te.text << "\n";
    }
};

int main()
{
    TextEditor te{"Hello World"};

    te.add_word("!!!, New Word.");
    te.add_word(" Another Word");
    std::cout << "Original Text -> " << te;

    te.undo();
    std::cout << "Undo Once     -> " << te;
    te.undo();
    std::cout << "Undo Twice    -> " << te;
    te.undo();
    std::cout << "Undo Thrice   -> " << te;

    te.redo();
    std::cout << "Redo Once     -> " << te;

    return 0;
}