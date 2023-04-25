#ifndef BLOCK_CODE_H
#define BLOCK_CODE_H

#include <iostream>
#include <ctime> 
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <FileUtil.hh>
#include <Encoder.hh>
#include <Decoder.hh>


class BlockCode {
public:

  Encoder m_encoder;
  Decoder m_decoder;

  void encode(std::string in, std::string out) {
    m_encoder.encode(in, out);
  }

  void decode(std::string in, std::string out) {
    m_decoder.decode(in, out);
  }

};


#endif
