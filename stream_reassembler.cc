#include "stream_reassembler.hh"
using namespace std;
StreamReassembler::StreamReassembler(const size_t capacity)
    : size_unassemb(0)  
    , sto_buf(capacity, '\0')
    , _output(capacity)
    , map_bit(capacity, false)
    , _end_of_file(0)
    , next_assemb(0)
    , _cap(capacity) {}
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    size_t len_gth = data.length();
    //checking eof to be true or not
    if (eof==true) {
        _end_of_file = true;}
    if (_end_of_file==true ) {
         if(size_unassemb==0){
            if(len_gth==0){
        _output.end_input();
        return; }
        }
  }if (index>=next_assemb+_cap){return;}//Condition to check if index was valid or not
//condtion1
if (next_assemb<=index) {
size_t actual;
        int range=index-next_assemb;
        int remcap=_cap - _output.buffer_size()-range; 
        if(len_gth<remcap){
        actual=len_gth;}else{ actual=remcap;}    
        for (size_t i = 0; i < actual; i++) {
            if (map_bit[i + range]){continue;}
        size_unassemb=size_unassemb+1;
            map_bit[i + range] = true;
            sto_buf[i +range] = data[i];}
if (actual<len_gth) {
            _end_of_file= false; }
    } 
    //else if condition 
    else if (index+len_gth>next_assemb) {
    size_t actual;
        int range = next_assemb - index;
         if(_cap - _output.buffer_size()>len_gth-range){
         actual=len_gth-range;}else{actual=_cap - _output.buffer_size();}
        for (size_t i = 0; i < actual; i++) {
            if (map_bit[i]==true){continue;}
                map_bit[i] = true;
                size_unassemb=size_unassemb+1;
            sto_buf[i] = data[i +range]; }
         if (range<len_gth-actual) {_end_of_file = false; }
 } string tring = "";
    while (map_bit.front()==true) {
        tring = tring+sto_buf.front();
        map_bit.pop_front();
        sto_buf.pop_front();
        map_bit.push_back(false);
        sto_buf.push_back('\0');   }
        int sze=tring.length();
    if (sze > 0) { _output.write(tring);
        next_assemb = sze+next_assemb;
       size_unassemb = size_unassemb- sze;}
    if (size_unassemb== 0)
        {if(_end_of_file==true)
        { _output.end_input();
        }
        }

    }
bool StreamReassembler::empty() const { return size_unassemb == 0; }
size_t StreamReassembler::ack_index() const { return next_assemb; }
size_t StreamReassembler::unassembled_bytes() const { return size_unassemb; }
