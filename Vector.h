#ifndef _VECTOR_H
#define _VECTOR_H

/*
 * The next line is used because Codewarrior has a conflict with
 * the STL Vector. Make sure to put the #include of this file
 * AFTER all the system includes.
 */

class ArrayIndexOutOfBounds { };

template <class Object>
class Vector
{
  public:
    explicit Vector( int theSize = 0 ) : currentSize( theSize )
      { objects = new Object[ currentSize ]; }
    Vector( const Vector & rhs ) : objects( NULL )
      { operator=( rhs ); }
    ~Vector( )
      { delete [ ] objects; }

    int size( ) const
      { return currentSize; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }


    const Vector & operator = ( const Vector & rhs );
    void resize( int newSize );
  private:
    int currentSize;
    Object * objects;
};

#include "Vector.cpp"
#endif


