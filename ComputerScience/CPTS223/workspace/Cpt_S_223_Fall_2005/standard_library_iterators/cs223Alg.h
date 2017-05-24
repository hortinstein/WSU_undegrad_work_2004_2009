#ifndef CS223ALG_H   // include guard
#define CS223ALG_H
///////////////////////////////////////////////////////////////////////////////
/// \author       Alex Hortin
/// \date         10/10/05
/// \brief        This file is made to implement standard library functions.
///
/// In this file I will implement 3 functions from the standard library they 
/// will all be finalized template functions that I will use to test out the 
/// compatability with the iterator and vector class I am currently using.
///
/// REVISION HISTORY:
///
/// NONE
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//



// LOCAL INCLUDES
//
#include "cs223Alg.h"              

// FUNCTIONS

///////////////////////////////////////////////////////////////////////
/// isPalindrome
/// \pre    a string has to be imputed
/// \post   NONE
/// \param  beg is the beginning of the range to search
/// \param  end is the ending of the range to search
/// \return a bool if its a predicate
///////////////////////////////////////////////////////////////////////
template <class BidirectionalIterator>
bool isPalindrome(BidirectionalIterator beg, BidirectionalIterator end ) 
{
   end--;
   unsigned int size = end - beg;
   unsigned int i = 0;
   while (i < size)
   {
      if (*beg != *end)
      {
         return false;
      }
      end--;
      beg++;
      i++;
   }
   return true;
}

///////////////////////////////////////////////////////////////////////
/// bubbleSort
/// \pre    An unsorted algorythm
/// \post   The array will be sorted
/// \param  two iterators that give a range of elements to be sorted
/// \return NONE
///////////////////////////////////////////////////////////////////////
template <class ForwardIterator>
void bubbleSort( ForwardIterator beg, ForwardIterator end )
{
   typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
   value_type temp;
   
   --end;
   ForwardIterator left = beg;
   ForwardIterator leftplus = beg;
   while (beg != end)
   {
      leftplus++;
      while (left != end)
      {
         if (*left > *leftplus)
         {
            temp = *left;
            *left = *leftplus;
            *leftplus = temp;
         }
         left++;
         leftplus++;
      }
      
      left = beg;
      leftplus = beg;
      end--;
   }
}

///////////////////////////////////////////////////////////////////////
/// findNIf
/// \pre    A container containing elements
/// \post   An iterator is returned to the place
/// \param  2 iteratos an it and a predicate fuction
/// \return the iterator that it was given..
///////////////////////////////////////////////////////////////////////
template <class InputIterator, class Pred>
InputIterator findNIf( InputIterator beg, InputIterator end, unsigned int count, Pred op )
{
   unsigned int i;
   InputIterator temp = beg;
   while (beg != end)
   {
      
      if (op(*beg))
      {
         if (i == 0)
         {
            temp = beg;
         }
         i++;
         if (i == count)
         {
            return temp;
         }
            
      }
      else 
      {
         i = 0;
      }
      beg++;
   }
   return end;
}

bool moreThanFive(int i)
{
   return i > 5;
}

#endif

