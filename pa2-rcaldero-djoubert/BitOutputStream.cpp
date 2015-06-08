#include <iostream>
#include <bitset>
#include "BitOutputStream.hpp"


  void BitOutputStream::flush(){
    out.put(buf);
    out.flush();
    buf = 0;
    bufi = 7;
   }

  /** Write the least significant bit of the argument into
   *  the bit buffer, and increment the bit buffer index.
   *  Flush to the ostream first if the bit buffer is full.
   *  This must be consistent with BitInputStream::readBit().
   */
  void BitOutputStream::writeBit(int bit) {
    if( bufi == -1 ){
      flush();
    }
    buf = buf | (bit << bufi);
    bufi--;
  }

  /** Write the least significant byte of the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing bytes.
   */
  void writeByte(int b) {
    ;
  }
  
  /** Write the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing ints.
   */
  void writeInt(int i) {
    ;
  }

