#include <cassert> // Provides assert
#include <cstdlib> // Provides size_t
#include <set>     // Provides set
#include <string>

namespace main_savitch_15
{
    template <class Item> // The purpose of this helper function is to round off the .5 created by the intital return
    int graph<Item>::find_longest(std::size_t source, std::size_t target) const
    {
        return find_longest_helper(source, target);
    }

    template <class Item> // FIND LONGEST
    double graph<Item>::find_longest_helper(std::size_t source, std::size_t target) const
    {
        double maxlength = 0;
        double templength;
        if (source == target) // base case, source = target
            return .5;        //.5 is being returned as a way of letting parent call know target was found

        for (int i = 0; i < size(); ++i)
        { // for each neighbor of current source node, call find_longest recursively
            if (edges[source][i])
            {
                templength = find_longest_helper(i, target);
                if (templength > maxlength) // out of all these calls, remember only the longest path
                    maxlength = templength;
            }
        }
        if (fmod(maxlength, 1) == 0) // if unable to find target in current path (no .5), return 0
            return 0;

        return 1 + maxlength; // target found previously, add length of current edge and return;
    }

    template <class Item>
    const std::size_t graph<Item>::MAXIMUM;

}
