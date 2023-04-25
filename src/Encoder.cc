#include <Encoder.hh>
#include <FileUtil.hh>


void Encoder::encode(std::string in, std::string out) {

  //std::vector<char> encoded_buffer = blocks_to_buffer(data_to_blocks(FileUtil::read_all_bytes(in)));

  //read file bytes
  std::vector<char> file_buffer = FileUtil::read_all_bytes(in);

  //hamming encode that byte buffer into a hamming blocks
  std::vector<std::bitset<8>> hamming_blocks = data_to_blocks(std::move(file_buffer)); 

  //convert those hamming blocks to bytes to be written out, sent over the wire, etc.
  std::vector<char> encoded_buffer = blocks_to_buffer(std::move(hamming_blocks));

  //write the buffer to a file for now, we will modify that file to test resilence 
  FileUtil::write_file(out, encoded_buffer);  
    
}

std::bitset<8> Encoder::hamming_encode(std::bitset<4> data) {

  //the 8 bit hamming block
  std::bitset<8> hamming;

  //put our data in bit positon 3, 5, 6, 7
  uint32_t offset {3};
  for (uint32_t i = 0; i < 4; ++i) {

    hamming[i + offset] = data[i];

    if (i == 0) {
      ++offset;
    }

  }

  //check the parity of all bit indexes where the data is 1
  std::bitset<4> parity{0};
  for (uint32_t i = 0; i < 8; ++i) {
    if (hamming[i] == 0) continue;

    parity = parity ^ std::bitset<4>(i);

  }

  //now we get something like this : 0011
  //meaing we need to set the check bits 0010 and 0001
  //we need to set the parity bit controlling each position (1,2,4)
  for (uint32_t i = 0; i < 4; ++i) {
    if (not parity[i]) continue;

    uint32_t index = static_cast<uint32_t>(pow(2, i));
    hamming[index] = 1;

  }

  return hamming;
}


//because of our hammign split, each hamming block gets half a byte
std::vector<std::bitset<4>> Encoder::split_byte(char c) {

  std::bitset<8> as_bits = std::bitset<8>(c);
  std::bitset<4> first;
  std::bitset<4> second;

  for (uint32_t i = 0; i < 8; ++i) {
    if (i < 4) {
      first[i] = as_bits[i];
    }
    else {
      second[i - 4] = as_bits[i];
    }
  }

  return {first, second};
}

std::vector<std::bitset<8>> Encoder::data_to_blocks(std::vector<char>&& data) {

  std::vector<std::bitset<8>> bs;

  for (const char& byte : data) {

    std::vector<std::bitset<4>> nibbles = split_byte(byte);
    if (nibbles.size() != 2) {
      std::cout << "issue byte splitting!\n";
      continue;
    }

    //std::cout << "encoding : " << byte << " as " << hamming_encode(nibbles[0]) << " and " << hamming_encode(nibbles[1]) << "\n";
    bs.push_back(hamming_encode(nibbles[0]));
    bs.push_back(hamming_encode(nibbles[1]));

  }

  return bs;

}

std::vector<char> Encoder::blocks_to_buffer(std::vector<std::bitset<8>>&& blocks) {
  std::vector<char> buffer;
  for (auto& block : blocks) {
    buffer.push_back(static_cast<unsigned char>(block.to_ulong()));
  }
  return buffer;
}


