#include <cstdlib> // Provides size_t
#include <iostream>
#include "set.h"

template <class Item>
main_savitch_11::set<Item>::set()
{
    data_count = 0;
    child_count = 0;
}

template <class Item>
main_savitch_11::set<Item>::set(const set &source)
{
    data_count = source.data_count;
    child_count = source.child_count;
    for (std::size_t i = 0; i < data_count; i++)
    {
        data[i] = source.data[i];
    }
    for (std::size_t i = 0; i < child_count; i++)
    {
        subset[i] = new set(*source.subset[i]);
    }
}
// Public functions
template <class Item>
void main_savitch_11::set<Item>::clear()
{ // clear function
    if (child_count == 0)
    { // base case, no children
        for (int i = 0; i < data_count; i++)
        { // wipe data array
            data[i] = 0;
        }
        for (int i = 0; i < child_count; i++)
        { // wipe pointer array
            delete[] subset[i];
        }
        data_count = 0;
        child_count = 0;
        return;
    }
    else
    {
        for (int i = 0; i < child_count; i++)
        { // recursive call on each child
            subset[i]->clear();
        }
    }
}
template <class Item>
bool main_savitch_11::set<Item>::insert(const Item &entry) // insert for root
{
    Item middle;
    Item data1[MAXIMUM + 1];
    Item data2[MAXIMUM + 1];
    set *subset1[MAXIMUM + 2];
    set *subset2[MAXIMUM + 2];

    if (child_count == 0)
    { // If root has no children and overflows, split
        if (!loose_insert(entry))
        {
            middle = data[MAXIMUM / 2 + 1];

            for (int i = 0; i < data_count / 2; i++)
                data1[i] = data[i];

            for (int i = data_count / 2 + 2; i < data_count; i++)
                data2[i - data_count / 2 + 2] = data[i];

            for (int i = 0; i < child_count / 2; i++)
                subset1[i] = data[i];

            for (int i = child_count / 2 + 2; i < child_count; i++)
                subset2[i] = data[i];

            subset[0] = subset1; // assign values to new children
            subset[1] = subset2;
            data[0] = data1;
            data[1] = data2;

            data_count = 1; // set root to middle value
            data[0] = middle;
        }
        return true;
    }
    else
    { // root has cildren, call insert on those children
        middle = fix_excess(entry);
        if (middle > 0)
            loose_insert(middle);
    }
    return false;
}

template <class Item>
void main_savitch_11::set<Item>::fix_excess(std::size_t entry) // acts as an insert but for non-root nodes
{
    int slot = 0;
    Item temp;
    Item temp1;
    Item data1[MAXIMUM + 1];
    set *subset1[MAXIMUM + 2];
    Item data2[MAXIMUM + 1];
    set *subset2[MAXIMUM + 2];

    if (child_count != 0)
    { // if not leaf, go down further
        std::cout << "went down" << '\n';
        for (int i = 0; i < data_count; i++)
        {
            if (entry < data[i])
                slot = i;
            i = data_count;
        }
        temp1 = subset[slot]->insert(entry); // call recursivly. If nothing is returned, finish. If an item is returned, split child nodes.
        std::cout << "gothere" << '\n';
        if (temp1 == 0)
        {
            std::cout << "good insert" << '\n';
        }
        else
        {
            loose_insert(temp1);
            set<Item> s1;
            set<Item> s2;

            for (int i = 0; i < subset[slot]->data_count / 2; i++) // break up children/return
                subset[child_count]->data[i] = subset[slot]->data[i];

            for (int i = subset[slot]->data_count / 2; i < subset[slot]->data_count; i++)
                subset[child_count]->data[i - subset[slot]->data_count / 2] = subset[slot]->data[i];

            for (int i = 0; i < subset[slot]->child_count / 2; i++)
                subset[child_count]->subset[i] = subset[slot]->subset[i];

            for (int i = subset[slot]->child_count / 2; i < subset[slot]->child_count; i++)
                subset[child_count]->subset[i - subset[slot]->child_count / 2] = subset[slot]->subset[i];

            child_count++;
        }
    }
    // Leaf found. Try inserting. If overflow, return middle value and delete it
    if (!loose_insert(entry))
    {
        std::cout << "max oveflow" << '\n';
        temp = data[MAXIMUM / 2];
        erase(data[MAXIMUM / 2]);
    }
}

template <class Item>
std::size_t main_savitch_11::set<Item>::erase(const Item &target) // recursive erase
{
    int tempindex = 0;
    bool found = false;
    for (int i = 0; i < data_count; i++)
    {
        if (data[i] == target)
        {
            std::cout << "removing " << data[i] << '\n';
            tempindex = i;
            found = true;
        }
    }
    if (found)
    {
        for (int j = tempindex; j < data_count - 1; j++)
        { // if found, shift over rest of array
            data[j] = data[j + 1];
        }
        data_count--;
        if (data_count < MINIMUM)
        {
            fix_shortage(data_count / 2);
            return 1;
        }
        return 1;
    }
    for (int i = 0; i < child_count; i++)
        subset[i]->erase(target);
}

template <class Item>
std::size_t main_savitch_11::set<Item>::count(const Item &target) const
{ // count function
    std::size_t num = 0;
    for (int i = 0; i < data_count; i++)
    { // check array
        if (data[i] == target)
            num++;
    }
    for (int i = 0; i < child_count; i++)
    { // recursive call on each child
        num += (subset[i]->count(target));
    }
    return num;
}

template <class Item>
void main_savitch_11::set<Item>::print(int indent) const
{ // int indent) {
    for (int i = 0; i < data_count; i++)
    { // check array
        std::cout << data[i] << '\n';
    }
    for (int i = 0; i < child_count; i++)
    { // recursive call on each child
        subset[i]->print();
    }
    return;
}
// private functions
template <class Item>
bool main_savitch_11::set<Item>::loose_insert(const Item &entry)
{
    data[data_count] = entry;
    data_count++;
    if (data_count > MAXIMUM)
        return false;
    return true;
}

template <class Item>
bool main_savitch_11::set<Item>::loose_erase(const Item &target)
{
    for (int i = 0; i < data_count; i++)
    { // check array
        if (data[i] == target)
        {
            for (int j = i; j < data_count - 1; j++)
            { // if found, shift over rest of array
                data[j] = data[j + 1];
            }
            data_count--;
            return true;
        }
    }
    for (int i = 0; i < child_count; i++)
    { // recursive call on each child
        subset[i]->loose_erase(target);
    }
    return false;
}

template <class Item>
void main_savitch_11::set<Item>::remove_biggest(Item &removed_entry)
{
    Item temp = 0;
    int tempindex = 0;
    if (child_count == 0)
    { // base case, leaf
        for (int i = 0; i < data_count; i++)
        {
            if (data[i] >= temp)
            {
                temp = data[i];
                tempindex = i;
            }
        }
        for (int j = tempindex; j < data_count - 1; j++)
        { // if found, shift over rest of array
            data[j] = data[j + 1];
        }
        return;
    }

    subset[child_count - 1]->remove_biggest(removed_entry);
}

template <class Item>
void main_savitch_11::set<Item>::fix_shortage(std::size_t i)
{
}

// namespace main_savitch_11