#include <BlockCode.hh>
#include <FileUtil.hh>

#include <string>
#include <set>
#include <iostream>
#include <cstdlib>

int main() {
  
  BlockCode bcode;
  
  const std::string sourceFilePath {"../../data/foo.txt"};
  const std::string destFilePath {"../../data/bar.txt"};
  const std::string diskFilePath {"../../data/disk.bin"};

  //binary is in demo/build/bin
  //data is in   demo/data/
  bcode.encode(sourceFilePath, diskFilePath);
  
  //now we mess with our disk...
  FileUtil::murphy(diskFilePath);

  bcode.decode(diskFilePath, destFilePath);

  const std::string cmd {"diff " + sourceFilePath + " " + destFilePath};
  std::cout << "now we bash diff the source and dest files...\n";
  system(cmd.c_str());

}

