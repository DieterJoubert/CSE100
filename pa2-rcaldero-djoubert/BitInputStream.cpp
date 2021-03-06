#include <iostream>
#include <bitset>
#include "BitInputStream.hpp"

    /** Read the next bit from the bit buffer.
     *  If the bit buffer is currently empty,
     *  fill the bit buffer by reading a char from the istream first.
     *  Return the bit read as the least signficant bit of an int.
     *  Return -1 on EOF.
     *  This must be consistent with BitOutputStream::writeBit(), in terms
     *  of ordering of bits in the stream.
     */
    int BitInputStream::readBit() {
      if( bufi == -1 ){
        BitInputStream::fill();
        if (in.eof()) {
          return -1;
        }
      }
      if( (buf >> bufi & 0x1) == 1 ){
        bufi--;
        return 1;
      }
      else if ( (buf >> bufi & 0x1) == 0 ){
        bufi--;
        return 0;
      }
      return -1;
    }

    /** Read a byte from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading bytes.
     */
    int readByte() {
      return -1;
    }

    /** Read a non-negative int from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading ints.
     */
    int readInt() {
      return -1;
    } 
