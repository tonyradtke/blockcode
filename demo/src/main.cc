#include <Partitioner.hh>

#include <string>
#include <set>
#include <iostream>

class setPart : public Partitioner<std::set<std::string>> {
public: 

  setPart(std::set<std::string>& data, int numParts) 
    : Partitioner(data, numParts) {}

  void handle_partition(std::set<std::string>::const_iterator f_begin, std::set<std::string>::const_iterator f_end) {
    for (auto it = f_begin; it != f_end; ++it) { 
    }
  }

};


int main() {

  std::set<std::string> s;

  for (int i = 0; i < 100; ++i) {
    s.insert(std::to_string(i));
  }

  setPart vp(s, 5);

  vp.execute();


}

