<h2> Introduction </h2>

  - Simple implementation and demo of Hamming error correction codes  

  <br>

  <p>
    BlockCode class uses a Hamming(7,4) encoding to encode and decode filedata 
  </p>

  <br>

  - Create your BlockCode class and send it a data file path and storage file path
  
  ```cpp

    BlockCode bcode;
    bcode.encode("data.txt", "disk")

  ```

  - then simulate some error happening to the transfer of information : 

  ```cpp
  
    FileUtil::murphy("disk");

  ```

   - finally decode the error ridden file back into the original information

  ```cpp
  
    bcode.decode("disk", "decoded.txt");

  ```


<h2> Building </h2>

<ol>
 <li> Download, Build and Install blockcode demo with CMake 
    <ul>
      <li> git clone https://github.com/tonyradtke/blockcode.git </li>
      <li> cd blockcode </li>
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
      <li> include BlockCode.hh and FileUtil.hh in your project </li>
    </ul> 
  </li>
  <br>
</ol>




