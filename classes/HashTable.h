/*
 * File:   HashTable.h
 * Author: allada
 *
 * Created on December 6, 2013, 7:01 PM
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#pragma once


#define NULL 0

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

inline uint32_t upper_power_of_two(uint32_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

inline uint64_t upper_power_of_two(uint64_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
}

// from code.google.com/p/smhasher/wiki/MurmurHash3
inline uint32_t integerHash(uint32_t h)
{
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return h;
}

// from code.google.com/p/smhasher/wiki/MurmurHash3
inline uint64_t integerHash(uint64_t k)
{
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccd;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53;
	k ^= k >> 33;
	return k;
}

//----------------------------------------------
//  HashTable
//
//  Maps pointer-sized integers to pointer-sized integers.
//  Uses open addressing with linear probing.
//  In the m_cells array, key = 0 is reserved to indicate an unused cell.
//  Actual value for key 0 (if any) is stored in m_zeroCell.
//  The hash table automatically doubles in size when it becomes 75% full.
//  The hash table never shrinks in size, even after Clear(), unless you explicitly call Compact().
//----------------------------------------------
#include "Order.h"
class HashTable
{
public:
    struct Cell
    {
        size_t key;
        Order *value;
    };

private:
    Cell* m_cells;
    size_t m_arraySize;
    size_t m_population;
    bool m_zeroUsed;
    Cell m_zeroCell;

    void Repopulate(size_t desiredSize);

public:
    HashTable(size_t initialSize = 8);
    ~HashTable();

    // Basic operations
    Cell* Lookup(size_t key);
    Cell* Insert(size_t key);
    void Delete(Cell* cell);
    void Clear();
    void Compact();

    void Delete(size_t key)
    {
        Cell* value = Lookup(key);
        if (value)
            Delete(value);
    }

    //----------------------------------------------
    //  Iterator
    //----------------------------------------------
    friend class Iterator;
    class Iterator
    {
    private:
        HashTable& m_table;
        Cell* m_cur;

    public:
        Iterator(HashTable &table);
        Cell* Next();
        inline Cell* operator*() const { return m_cur; }
        inline Cell* operator->() const { return m_cur; }
    };
};

#endif	/* HASHTABLE_H */

