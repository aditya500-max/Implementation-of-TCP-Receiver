#include "tcp_receiver.hh"
#include <algorithm>

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader head = seg.header();
   //creating bool variables for each of syn&fin
   bool fin=head.fin;
   bool syn=head.syn;
   bool end_of_file=false;
   //checking condition for no SYN flag 
   string data=seg.payload().copy();
   if(syn==false){
     if(_synReceived==false){
          return;
    }
   }
    
    //condition for 1st SYN arrival
   if(_synReceived==false){
      if(syn==true){
          _isn=head.seqno;
          _synReceived=true;
      }
   }
   if(_synReceived==false){
      if(syn==true){
          if(fin==true){
            end_of_file=true;
            _finReceived=true;
          }
          _reassembler.push_substring(data,0,end_of_file);
          return;
      }
   }//checking if FIN received
   if(fin==true){
     if(_synReceived==true){
        end_of_file=true;
        _finReceived=true;
    }
   }        
_reassembler.push_substring(data,unwrap(head.seqno, _isn, _reassembler.ack_index()) - _synReceived, end_of_file);
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    uint64_t absack_no=_reassembler.stream_out().bytes_written()+1;
    optional<WrappingInt32> ull = nullopt;
    if(_synReceived==false){return ull;}
    //condition
    if(_reassembler.stream_out().input_ended()==true){ ++absack_no; }
    return WrappingInt32(_isn)+absack_no;
}

size_t TCPReceiver::window_size() const { 
    uint64_t result=_capacity - _reassembler.stream_out().buffer_size();
    return result;
  }


