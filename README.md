<h2> Introduction </h2>

  - This is designed to be a lightweight template to facilitate parallel processing of iterator based containers

  <br>

  <p>
    Simply create a class inhereting from Partitioner templatized by some actual type T. Then override the constructor
    and handle_partition function. Once initialized, this new class will spawn worker threads once execute() is called. 
  </p>

  <br>

  - Here we create a simple child class.
  
  <code>
    class setPartitioner : public Partitioner<std::set<std::string>> {
      public: 

      setPartitioner(std::set<std::string>& data, int numParts) 
        : Partitioner(data, numParts) {}

      void handle_partition(std::set<std::string>::const_iterator f_begin, std::set<std::string>::const_iterator f_end) {
        for (auto it = f_begin; it != f_end; ++it) { 
          handle_element(*it)
        }   
      }
    };

  </code>

  - Which can then be ran like : 

  <code>
    std::set<std::string> s;

    for (int i = 0; i < 100; ++i) {
      s.insert(std::to_string(i));
    }

    setPartitioner parter(s, 5); 

    parter.execute();
  </code>
  

<h2> Dependencies </h2>

  - [cppzmq](https://github.com/zeromq/cppzmq)


<h2> Building </h2>

<ol>
  <li> Download and build Dependencies <
    <ul>
      <li> download cppzmq : https://github.com/zeromq/cppzmq </li>
      <li> follow the build instructions </li>
    </ul>
  </li>
  <br>
  <li> Download, Build and Install simple-zmq-server with CMake 
    <ul>
      <li> git clone https://github.com/tonyradtke/simple-zmq-server.git </li>
      <li> cd simple-zmq-server </li>
      <li> mkdir build </li>
      <li> cd build </li>
      <li> cmake .. </li>
      <li> make install </li>
    </ul>
  </li>
  <br>
  <li>  Build and Run the demo to make sure things are working 
    <ul> 
      <li> cd demo </li>
      <li> mkdir build </li>
      <li> cd build </li>
      <li> cmake . </li>
      <li> make </li>
      <li> ./bin/__demo__ </li>
    </ul>
  </li>
  <br>
  <li> Include and Link against simple-zmq-server and cppzmq in your project </li>
    <ul>
      <li> find_library("simple-zmq-server" STATIC lib) </li>
      <li> find_package(cppzmq) </li>
      <li> target_link_libraries(${YOUR_BINARY} PUBLIC "simple-zmq-server") </li>
      <li> target_link_libraries(${YOUR_BINARY} PUBLIC cppzmq) </li>
    </ul> 
  </li>
  <br>
</ol>




