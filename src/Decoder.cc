#include <Decoder.hh>

void Decoder::decode(std::string in, std::string out) {
  
  //read in (encoded) bytes from file
  std::vector<char> read_buffer = FileUtil::read_all_bytes(in);

  //conver that byte buffer to blocks to be hamming decoded (bitsets for ease of use)
  std::vector<std::bitset<8>> file_blocks = buffer_to_blocks(std::move(read_buffer));
  
  //hamming decode (correct) the blocks into our original bytes
  std::vector<char> decoded_buffer = blocks_to_data(std::move(file_blocks));

  FileUtil::write_file(out, decoded_buffer);

}

std::bitset<4> Decoder::hamming_decode(std::bitset<8> hamming) {

  //first we check the parity and correct if we can 
  std::bitset<4> data;
  std::bitset<3> parity{0};
  for (uint32_t i = 0; i < 8; ++i) {
    if (hamming[i] == 0) continue;

    parity = parity ^ std::bitset<3>(i);

  }

  //no errors, extract and return data
  if (parity.none()) {
    uint32_t offset {3};
    for (uint32_t i = 0; i < 4; ++i) {

      data[i] = hamming[i + offset];

      if (i == 0) {
        ++offset;
      }
    }
    return data;
  }

  //found an error, fix 
  //parity has the index of the issue in binary 
  uint32_t index = static_cast<uint32_t>(parity.to_ulong());
  hamming.flip(index);

  //now that the error is fixed, get the data out again
  uint32_t offset {3};
  for (uint32_t i = 0; i < 4; ++i) {

    data[i] = hamming[i + offset];

    if (i == 0) {
      ++offset;
    }
  }

  return data;
  
}

char Decoder::build_byte(std::bitset<4> l, std::bitset<4> r) {

  std::bitset<8> bs;
  for (uint32_t i = 0; i < 8; ++i) {
    if (i < 4) {
      bs[i] = l[i];
    }
    else {
      bs[i] = r[i - 4];
    }
  }

  return static_cast<unsigned char>(bs.to_ulong());

}

std::vector<char> Decoder::blocks_to_data(std::vector<std::bitset<8>>&& blocks) {
  std::vector<char> data;

  for (uint32_t i = 0; i < blocks.size() - 1; ++i) {
    std::bitset<4> l = hamming_decode(blocks[i]);
    std::bitset<4> r = hamming_decode(blocks[i + 1]);

    char c = build_byte(l, r);

    data.push_back(c);
    ++i;

  }

  return data;
}
std::vector<std::bitset<8>> Decoder::buffer_to_blocks(std::vector<char>&& buffer) {
  std::vector<std::bitset<8>> blocks;

  for (auto& byte : buffer) {
    blocks.push_back(std::bitset<8>(byte));
  }

  return blocks;
}

