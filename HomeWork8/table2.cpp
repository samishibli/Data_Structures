#include <cassert> // Provides assert
#include <cstdlib> // Provides size_t
#include <iostream>
#include "table2.h"

template <class RecordType>
table<RecordType>::table()
{
  total_records = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    data[i] = NULL;
  }
}

template <class RecordType>
table<RecordType>::table(const table &source)
{
  node<RecordType> *tempTail;

  // initialize and copy values
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    list_copy(source.data[i], data[i], tempTail);
  }
  this->total_records = source.total_records;
}

template <class RecordType>
table<RecordType>::~table()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    list_clear(data[i]);
  }
}

template <class RecordType>
void table<RecordType>::insert(const RecordType &entry)
{
  if (!is_present(entry.key))
  {
    node<RecordType> *select = data[hash(entry.key)];
    if (select == NULL)
    {
      select = data[hash(entry.key)] = new node<RecordType>;
      select->data = entry;
      select->link = NULL;
    }
    else
    {
      while (select->link != NULL && select->data.key != entry.key)
      {
        select = select->link;
      }

      select->link = new node<RecordType>;
      select = select->link;
      select->link = NULL;
      select->data = entry;
    }
    total_records++;
  }
}

template <class RecordType>
void table<RecordType>::remove(int key)
{
  node<RecordType> *select = data[hash(key)],
                   *pastselect = NULL;
  // First find the node for deletion
  bool found = false;
  while (select != NULL)
  {
    // search for node containing key
    if (select->data.key == key)
    {
      found = true;
      break;
    }
    pastselect = select;
    select = select->link;
  }
  if (found == true)
  {
    list_remove(pastselect);
    total_records--;
  }
  // Otherwise no node to delete so do nothing
}

template <class RecordType>
void table<RecordType>::operator=(const table &source)
{
  if (this == &source)
    return;
  // Otherwise we need to clear data from heap
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    list_clear(data[i]);
  }
  node<RecordType> *tempTail;
  // initialize and copy values
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    list_copy(source.data[i], data[i], tempTail);
  }
  this->total_records = source.total_records;
}

template <class RecordType>
void table<RecordType>::find(int key, bool &found, RecordType &result) const
{
  node<RecordType> *select = data[hash(key)];
  found = false;
  while (select != NULL && select->data.key != key)
  {
    if (select->data.key == key)
    {
      // found it
      found = true;
      result = select->data;
      break;
    }
    // keep going
    select = select->link;
  }
}

template <class RecordType>
bool table<RecordType>::is_present(int key) const
{
  node<RecordType> *select = data[hash(key)];
  bool found = false;
  while (select != NULL)
  {
    if (select->data.key == key)
    {
      // find match
      found = true;
      break; // exit
    }
    select = select->link; // otherwise keep going
  }
  return found;
}

template <class RecordType>
std::size_t table<RecordType>::hash(int key) const
{
  // Find the index we want to assign to
  return key % TABLE_SIZE;
}
