#ifndef SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
#define SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
#include "byte_stream.hh"
#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <string>
class StreamReassembler {
  private:
    size_t size_unassemb;        
    bool _end_of_file;            
    std::deque<bool> map_bit;
    size_t next_assemb; 
    std::deque<char> sto_buf; 
    ByteStream _output;  
    size_t _cap;    
    void check_contiguous();
     size_t real_size(const std::string &data, const size_t index);
  public:
    StreamReassembler(const size_t capacity);   
    void push_substring(const std::string &data, const uint64_t index, const bool eof);   
    const ByteStream &stream_out() const { return _output; }
    ByteStream &stream_out() { return _output; }   
    size_t unassembled_bytes() const;    
    bool empty() const; 
    size_t ack_index() const;
};
#endif  // SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
