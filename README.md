<h2> Introduction </h2>

  - This is designed to be a lightweight template to facilitate parallel processing of iterator based containers

  <br>

  <p>
    Simply create a class inhereting from Partitioner templatized by some actual type T. Then override the constructor
    and handle_partition function. Once initialized, this new class will spawn worker threads once execute() is called. 
  </p>

  <br>

  - Here we create a simple child class.
  
  '''cpp

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
 '''

  - Which can then be ran like : 

  '''cpp

    std::set<std::string> s;

    for (int i = 0; i < 100; ++i) {
      s.insert(std::to_string(i));
    }

    setPartitioner parter(s, 5); 

    parter.execute();
  ''' 

<h2> Dependencies </h2>

  - [cppzmq](https://github.com/zeromq/cppzmq)


<h2> Building </h2>

<ol>
 <li> Download, Build and Install partitioner with CMake 
    <ul>
      <li> git clone https://github.com/tonyradtke/partitioner.git </li>
      <li> cd partitioner </li>
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
  <li> Include partitioner in your project </li>
    <ul>
      <li> include_directories(${YOUR_INCLUDE_DIR})  </li>
      <li> #include <Partitioner.hh> </li>
    </ul> 
  </li>
  <br>
</ol>




