/**
 * @cite State Pattern states that state machines are created that facilitates the transitioning of an object from one state to another based on either a change in internal state or triggered by an external event.
 * Aims at promoting loose coupling and Extensible code as the state specific code is divided into separate entities making it easier to add new states and altering previous states.
 *
 * @brief State Pattern can be exemplified by a state machine that denotes the states of interaction of a person on instagram.
 */

#include <iostream>
#include <map>
#include <vector>

// Possible states the person might be currently in or can be in.
enum State
{
    open_instagram,
    stalk_someone,
    doom_scroll,
    comment,
    check_stories,
    like,
    check_posts,
    open_reels,
    close_instagram
};

// Printing the state in textual format.
std::ostream &operator<<(std::ostream &oss, const State &s)
{
    switch (s)
    {
    case open_instagram:
        std::cout << "Home Page...";
        break;
    case stalk_someone:
        std::cout << "Stalk Someone (Be careful)...";
        break;
    case doom_scroll:
        std::cout << "Doom Scroll (Be Careful)...";
        break;
    case check_posts:
        std::cout << "Check New Posts ...";
        break;
    case check_stories:
        std::cout << "Check New Stories ...";
        break;
    case like:
        std::cout << "Like (Be Careful if you're stalking) ... ";
        break;
    case comment:
        std::cout << "Comment (Make it thoughtful) ... ";
        break;
    case open_reels:
        std::cout << "Open Reels (Be Careful of Doom Scrolling) ... ";
        break;
    case close_instagram:
        std::cout << "Close Instagram ... ";
        break;

    default:
        break;
    }
    return oss;
}

int main()
{
    // Facilitates the transition from one state to another state.
    // Connects a state with multiple other states.
    std::map<State, std::vector<State>> states;

    // Connecting States with each other ...
    {
        states[open_instagram].push_back(check_posts);
        states[open_instagram].push_back(check_stories);
        states[open_instagram].push_back(open_reels);
        states[open_instagram].push_back(close_instagram);

        states[check_posts].push_back(stalk_someone);
        states[check_posts].push_back(like);
        states[check_posts].push_back(comment);
        states[check_posts].push_back(open_instagram);
        states[check_posts].push_back(close_instagram);

        states[check_stories].push_back(stalk_someone);
        states[check_stories].push_back(like);
        states[check_stories].push_back(open_instagram);
        states[check_stories].push_back(close_instagram);

        states[stalk_someone].push_back(check_posts);
        states[stalk_someone].push_back(like);
        states[stalk_someone].push_back(open_instagram);
        states[stalk_someone].push_back(close_instagram);

        states[open_reels].push_back(doom_scroll);
        states[open_reels].push_back(open_instagram);
        states[open_reels].push_back(close_instagram);

        states[doom_scroll].push_back(stalk_someone);
        states[doom_scroll].push_back(open_instagram);
        states[doom_scroll].push_back(like);
        states[doom_scroll].push_back(comment);
        // Creates an infinte loop of doom scrolling ...
        states[doom_scroll].push_back(doom_scroll);
        states[doom_scroll].push_back(close_instagram);
    }
    
    // Setting up intial and exit states ...
    State current_state = State::open_instagram, exit = State::close_instagram;

    // Simulating User Interaction with the app and transitioning based on the interaction...
    while (true)
    {
        std::cout << current_state << "\n";
        int option, i = 1;
        std::cout << "Make Your Choice\n";
        for (auto choice : states[current_state])
        {
            std::cout << "\t" << i++ << ". " << choice << ".\n";
        }
        std::cout << "Enter Your Choice :: ";
        std::cin >> option;
        if (option < 0 || option >= states[current_state].size())
        {
            std::cout << "Wrong Choice...\n";
            continue;
        }

        std::cout << "You choose to " << states[current_state][option] << ".\n";
        if (states[current_state][option] == like || states[current_state][option] == comment)
            continue;
        current_state = states[current_state][option];

        if (current_state == exit)
            break;
    }

    return 0;
}