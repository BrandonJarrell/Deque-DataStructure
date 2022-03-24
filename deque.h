/***********************************************************************
* Header:
*    Deque
* Summary:
*    This will contain the dynamic data
* Author
*    Brandon Jarrell
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>  
#include <iostream>


namespace custom
{

   /************************************************
    * QUEUE
    * A class that holds stuff
    ***********************************************/
   template <class T>
   class deque
   {
   private:
      T* array;
      int numElements;
      int numCapacity;     // Overall capacity
      int iFront;          // next item in the front of index that can be popped  
      int iBack;           // last item in the index right before being pushed


   public:
      // constructors and destructors
      deque() { numCapacity = 0; iFront = 0; iBack = 0; array = NULL; }
      deque(int numCapacity)                throw (const char *);              //non-default constructor
      deque(const deque& rhs)               throw (const char *);              //copy constuctor
      ~deque();

      deque& operator = (const deque& rhs) throw (const char *);  // Assignment operator


      int size() const { return iBack - iFront; }   // Returns the size
      bool empty();
      void clear();
      void push_back(T t)    throw(const char*);
      void push_front(T t)   throw(const char*);
      void pop_back()        throw(const char*);
      void pop_front()       throw(const char*);
      void resize()          throw(const char*);
      T& back()              throw(const char*);
      T& front()             throw(const char*);
      int iBackNormalized()  const throw(const char*);
      int iFrontNormalized()  throw(const char*);
      

      int  capacity() const { return numCapacity; }     // Returns maxSize

   };

   /************************************************
   * Back() returns the back of the deque
   ***********************************************/
   template <class T>
   T& deque <T> :: back() throw(const char*)
   {
      if (this->empty())
         throw "ERROR: attempting to access an element in an empty queue";
      return array[iBackNormalized()];
   }


   /************************************************
   * Front() returns the front of the deque
   ***********************************************/
   template <class T>
   T& deque <T> :: front() throw(const char*)
   {
      if (this->empty())
         throw "ERROR: attempting to access an element in an empty queue";
      return array[iFront + 1];
   }

   /*******************************************
    * popBack() reduced by one from the back
    *******************************************/
   template <class T>
   void deque <T> ::pop_back() throw(const char*)
   {
      if (!this->empty())
      {
         iBack--;
      }
      return;
   }


   /*******************************************
    * popFront() reduced by 1 from the front
    *******************************************/
   template <class T>
   void deque <T> :: pop_front() throw(const char*)
   {
      if (!this->empty())
      {
         iFront++;
      }
      return;
   }


   /*******************************************
    * Push_Back()  Push a value onto the back
    *******************************************/
   template <class T>
   void deque <T> ::push_back(T t) throw(const char*)
   {
         
      if (numCapacity == 0)  // If the capacity is 0, give it a space of 10
      {
         numCapacity = 10;

         try
         {
            array = new T[numCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Queue";
         }
      }

      if (iBack >= numCapacity)  // If the back of the deque is greater than or = to capacity, set it to NULL
      {
         T* temp = NULL;


         try                     // Then try and assign more space
         {
            temp = new T[numCapacity * 2];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Queue";
         }

         for (int i = 0; i < numCapacity; i++)  // And copy it over one by one
         {
            temp[i] = array[i];
         }

         delete[] array;                        //Clear the old array

         array = temp;                          // set it

         numCapacity *= 2;                   // if it was successful, do the same as the try.
      }

      iBack++;
      array[iBackNormalized()] = t;
      numElements++;

      return;  
   }


   /*******************************************
    * pushFront() : pushes 
    *******************************************/
   template <class T>
   void deque <T> :: push_front(T t) throw(const char*)
   {
      if (numCapacity == 0)  // If the capacity is 0, give it a space of 10
      {
         numCapacity = 10;

         try
         {
            array = new T[numCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Queue";
         }
      }

      if (iBack >= numCapacity)  // If the back of the deque is greater than or = to capacity, set it to NULL
      {
         T* temp = NULL;


         try                     // Then try and assign more space
         {
            temp = new T[numCapacity * 2];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a new buffer for Queue";
         }

         for (int i = 0; i < numCapacity; i++)  // And copy it over one by one
         {
            temp[i] = array[i];
         }

         delete[] array;                        //Clear the old array

         array = temp;                          // set it

         numCapacity *= 2;                   // if it was successful, do the same as the try.
      }
      iFront--;
      array[iFrontNormalized()] = t;
      numElements++;

      return;
   }


   /*******************************************
    * clear() :: clears out the deque
    *******************************************/
   template <class T>
   void deque <T> :: clear()
   {
      if (array != NULL)
         delete[] array;

      iFront = 0;
      iBack = 0;
      numCapacity = 0;
   }


   /*******************************************
    * Empty() Checks if its empty
    *******************************************/
   template <class T>
   bool deque <T> :: empty()
   {
      if ((iBack - iFront) == 0)
         return true;
      else
         return false;
   }

   /*******************************************
   * iFrontNormalized() Allows a negative number to be normalized
   *******************************************/
   template <class T>
   int deque <T> ::iFrontNormalized()
   {
      if ((iFront < 0) && (iFront % numCapacity != 0))
      {
         int normal = (iFront % numCapacity) + numCapacity;
         return normal;
      }

      return iFront % numCapacity;

   }

   /*******************************************
   *  iBackNormalized() Allows a negative number to be normalized
   *******************************************/
   template <class T>
   int deque <T> ::iBackNormalized() const
   {
      if ((iBack < 0) && (iBack % numCapacity != 0))
      {
         int normal = (iBack % numCapacity) + numCapacity;
         return normal;
      }
      return iBack % numCapacity;
      
   }


   /* CONSTRUCTORS BELOW */


   /************************************************
    * TEMPLATE CLASS
    *  Non-default Constructor
    ***********************************************/
   template <class T>
   deque <T> ::deque(int numCapacity) throw (const char *)
   {
      assert(numCapacity >= 0);

      if(numCapacity == 0)
      {
         this->iFront = 0;
         this->iFront = 0;
         this->numElements = 0;
         this->numCapacity = 0;
         this->array = NULL;

         return;
      }
      
      try
      {
         this->array = new T[numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "Cannot Use Non-Default Constructor";
      }

      this->iFront = 0;
      this->iFront = 0;
      this->numElements = 0;
      this->numCapacity = numCapacity;
   }
   /*******************************************
   * DE-CONSTRUCTOR
   *******************************************/
   template <class T>
   deque <T> :: ~deque()
   {
      if (array != NULL)
         delete[] array;
   }


   /*******************************************
    * COPY CONSTRUCTOR
    *******************************************/
   template <class T>
   deque <T> ::deque(const deque <T>& rhs) throw (const char *)
   {
      // do nothing if there is nothing to do
      if (rhs.iBack == 0)
      {
         iBack = 0;
         iFront = 0;
         array = NULL;
         return;
      }

     
      try  // attempt to allocate
      {
         array = new T[rhs.numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the variables
      this->numCapacity = rhs.numCapacity;
      this->iBack = rhs.iBack;
      this->iFront = rhs.iFront;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
      {
         array[i] = rhs.array[i];
      }
   }



   /***********************************************
     * Assign Deque
    ***********************************************/
   template <class T>
   deque <T> & deque <T> :: operator = (const deque <T>& rhs) throw (const char *)
   {
     if (numCapacity != rhs.capacity())
     {
        array = NULL;
        delete[] array;
        array = new T[rhs.capacity()];
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        iFront = rhs.iFront;
        iBack = iBack;

     }

      // Filling out the whole array
     for (int i = 0; i < rhs.size(); i++)
         array[i] = rhs.array[i];

      return *this;
   }
};

#endif // DEQUE_H

