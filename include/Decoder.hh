#ifndef ERRC_DECODER_H
#define ERRC_DECODER_H

#include <iostream>
#include <ctime> 
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <FileUtil.hh>

class Decoder {
public:

  void decode(std::string in, std::string out); 

  std::bitset<4> hamming_decode(std::bitset<8> hamming);

  char build_byte(std::bitset<4> l, std::bitset<4> r);

  std::vector<char> blocks_to_data(std::vector<std::bitset<8>>&& blocks);

  std::vector<std::bitset<8>> buffer_to_blocks(std::vector<char>&& buffer);

};


#endif
