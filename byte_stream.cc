#include "byte_stream.hh"
#include <algorithm>
using namespace std;
//my buffer name is _Queuing()
ByteStream::ByteStream(const size_t capa)
        :read_bytes_size(0),written_bytes_size(0),_Queuing(),total_cap_size(capa),_error(false),input_end(false)  {}                   

size_t ByteStream::write(const string &data) {
    
   //edge case1: checking for input_end flag
  if(input_end==true){
    return 0;
  }
  else{
    size_t max_can_write=total_cap_size-_Queuing.size();
    size_t actual_write;
    if(data.size()>max_can_write){
      actual_write=max_can_write;
    }
    else{
      actual_write=data.size();
    }
    size_t j=0;
    while(j!=actual_write){
       
      _Queuing.push_back(data[j]);
      j++;
    }
    written_bytes_size=written_bytes_size+actual_write;
    return actual_write;
  }
}
string ByteStream::peek_output(const size_t len) const {
  size_t peek;
    if(_Queuing.size()>len){
      peek=len;
    }
    else{
      peek=_Queuing.size();
    }
    return string(_Queuing.begin(),_Queuing.begin()+peek);
}
void ByteStream::pop_output(const size_t len) {
  size_t pop;
  //edge case: checking if data more than buffer size is popped out
  if(len>_Queuing.size()){
   set_error();
   return;
   }
    if(_Queuing.size()>len){
      pop=len;
    }
    else{
      pop=_Queuing.size();
    }
    size_t i=0;
    while(i!=pop){
      _Queuing.pop_front();
      i++;
    }
    read_bytes_size=read_bytes_size+pop;
}
std::string ByteStream::read(const size_t len) {
    //edge case: checking for empty input
    if(len==0){
       return "";
    }
    //edge case: checking for size of len condition
     if(len>_Queuing.size()){
   set_error();
   return "";
   }
    string str="";
    size_t k=0;
    read_bytes_size=read_bytes_size+len;
    while(k!=len){
      str=str+_Queuing.front();
      _Queuing.pop_front();
      k++;
    }
    return str;
}

void ByteStream::end_input() { 
  input_end=true;
}

bool ByteStream::input_ended() const { return input_end;}

size_t ByteStream::buffer_size() const {return _Queuing.size(); }

bool ByteStream::buffer_empty() const {return _Queuing.empty(); }

bool ByteStream::eof() const { return _Queuing.empty()&&input_ended(); }

size_t ByteStream::bytes_written() const { return written_bytes_size; }

size_t ByteStream::bytes_read() const { return read_bytes_size;  }

size_t ByteStream::remaining_capacity() const { if(total_cap_size<_Queuing.size()){
return 0;
}
else{
return total_cap_size-_Queuing.size();
 }
 }
