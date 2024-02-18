/**
 * @cite Strategy Pattern states that the exact behavior of a system can be specified at runtime.
 * Aims at promoting code reusability and flexibility by decoupling the
 *
 * @brief Strategy Pattern can be exemplified by a Sorting Class that can change the mode of sorting from Ascending and Descending.
 */

#include <algorithm>
#include <vector>
#include <iostream>

// Alternate Strategies for Sorting...
enum SortStrategies
{
    asc,
    desc
};

/**
 * @brief Sorts the data based on the strategy provided.
 */
class Sorter
{
    SortStrategies strategy;

public:
    Sorter(SortStrategies s = SortStrategies::asc) : strategy(s) {}

    // Sort the input based on the strategy...
    void sort(std::vector<int> &arr)
    {
        if (strategy == SortStrategies::desc)
            std::sort(arr.begin(), arr.end(), std::greater<int>());
        else
            std::sort(arr.begin(), arr.end(), std::less<int>());
    }

    // Set Strategy for the sorting...
    void set_strategy(SortStrategies s)
    {
        strategy = s;
    }
};

int main()
{
    std::vector<int> a{2, 53, 23, 4, 34, 673, 2};

    // Create Sorter with Ascending Strategy ...
    Sorter sorter;
    sorter.sort(a);

    std::cout << "Ascending  :: ";
    for(auto it:a) std::cout << it << " ";
    std::cout << std::endl;

    // Set Descending Strategy ...
    sorter.set_strategy(SortStrategies::desc);
    sorter.sort(a);
    
    std::cout << "Descending :: ";
    for(auto it:a) std::cout << it << " ";
    std::cout << std::endl;

    return 0;
}