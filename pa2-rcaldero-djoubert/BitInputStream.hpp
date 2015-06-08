#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <bitset>

using namespace std;

/** A class for reading bits (and ints) from an istream
 */
class BitInputStream {
private:
    char buf;            // the buffer of bits
    //bitset<8> buf;
    int bufi;           // the bit buffer index
    std::istream & in;  // the input stream

public:
  /** Initialize a BitInputStream object, given an istream.
   */
  BitInputStream(std::istream& s) : in(s){
    buf = 0;
    bufi = -1;
  }

    /** Read the next bit from the bit buffer.
     *  If the bit buffer is currently empty,
     *  fill the bit buffer by reading a char from the istream first.
     *  Return the bit read as the least signficant bit of an int.
     *  Return -1 on EOF.
     *  This must be consistent with BitOutputStream::writeBit(), in terms
     *  of ordering of bits in the stream.
     */
    int readBit();

    /** Read a byte from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading bytes.
     */
    int readByte();

    /** Read a non-negative int from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading ints.
     */
    int readInt();

    /** Fill the buffer from the input */
    void fill(){
      buf = in.get();
      bufi = 7;
    }    

};

#endif // BITINPUTSTREAM_HPP