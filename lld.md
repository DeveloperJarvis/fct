### LLD (Low-Level Design) of a File Compression Tool in C

Low-Level Design (LLD) involves breaking down the system into smaller components, focusing on the functionality, algorithms, and internal interactions. Here is an LLD for a file compression tool implemented in C, outlining the modules and their interactions without providing specific code.

---

### **1. Overview**

The file compression tool will compress and decompress files, primarily using algorithms like **Huffman coding** or **Run-Length Encoding (RLE)**. The program should support reading a file, compressing it, and saving the compressed file, as well as decompressing the file back to its original form.

### **2. Functional Components**

The tool consists of the following main components:

1. **File I/O Handling**

   - Responsible for reading input files and writing compressed/decompressed output files.

2. **Compression/Decompression Algorithm**

   - This module contains the core logic for compressing and decompressing files.

3. **Data Structures**

   - The internal data structures (e.g., trees, tables) that are used to hold and manipulate data during compression and decompression.

4. **User Interface**

   - Command-line interface (CLI) to accept user inputs and display results.

5. **Error Handling**

   - Handles all error cases (e.g., invalid file paths, unsupported file formats).

### **3. Component Breakdown**

#### 3.1 **File I/O Handling**

- **Functions**:

  - `open_file(file_path, mode)`: Opens a file in the specified mode (read, write).
  - `read_file(file_ptr, buffer, size)`: Reads data from the file into a buffer.
  - `write_file(file_ptr, buffer, size)`: Writes data from the buffer into the file.
  - `close_file(file_ptr)`: Closes the opened file.

- **Data Structures**:

  - `FILE *file_ptr`: Pointer to the file.
  - `char buffer[]`: Buffer to hold file contents for reading/writing.

- **Error Handling**:

  - Ensure that the file is successfully opened before performing any read/write operations.
  - Check if the file pointer is `NULL` after attempting to open a file.

#### 3.2 **Compression/Decompression Algorithm**

- **Compression**:

  - The algorithm compresses the file using a method like **Huffman Coding** or **Run-Length Encoding**.

  - **Huffman Encoding** involves creating a binary tree where frequently occurring characters are closer to the root, and rare characters are deeper.

  - **Functions**:

    - `build_frequency_table(file_data)`: Calculates frequency of each character.
    - `build_huffman_tree(freq_table)`: Builds the Huffman tree from the frequency table.
    - `generate_huffman_codes(tree)`: Generates Huffman codes from the tree.
    - `compress_data(file_data, huffman_codes)`: Encodes the data using the generated Huffman codes.

- **Decompression**:

  - The decompression algorithm uses the Huffman codes (or the compressed data) to revert the file back to its original form.

  - **Functions**:

    - `decode_data(compressed_data, huffman_tree)`: Decodes the compressed data using the Huffman tree.
    - `build_huffman_tree_from_file(file_data)`: Reconstructs the Huffman tree from the compressed file.
    - `decompress_data(compressed_data)`: Reverts the compressed data to its original form using the tree.

#### 3.3 **Data Structures**

- **Frequency Table**:

  - A hash map or array to store the frequency of each character in the file.

- **Huffman Tree**:

  - A binary tree structure where each node contains:

    - Character: the character in the file.
    - Frequency: how often the character appears.
    - Left/Right pointers: pointers to left and right child nodes in the tree.

- **Huffman Code Table**:

  - A mapping of characters to binary codes.

  - Data Structure:

    - `char character`: Represents the character.
    - `char *code`: Represents the binary code for the character.

#### 3.4 **User Interface**

- **Main Functions**:

  - `parse_command_line_arguments(argc, argv)`: Handles command-line arguments for compressing or decompressing files.

    - Options include the input file path, output file path, and mode (compress/decompress).

  - `display_help()`: Displays usage information to the user.

- **Error Handling**:

  - Check if the user provides valid file paths.
  - Ensure the correct operation mode (compress or decompress) is selected.

#### 3.5 **Error Handling**

- **File Errors**:

  - Check for missing files, incorrect file formats, and permission issues.

- **Algorithm Errors**:

  - Check if the data is correctly encoded/decoded.
  - Handle any memory allocation failures.

- **General Errors**:

  - Provide feedback to the user if there are issues with command-line inputs or if unsupported operations are requested.

### **4. Flow of Operations**

#### 4.1 **Compression Process**

1. The user invokes the program with the command to compress.
2. The program opens the input file and reads its contents.
3. The program builds a frequency table for the file data.
4. A Huffman tree is constructed based on the frequency table.
5. The program generates Huffman codes for each character.
6. It then encodes the file data using these Huffman codes.
7. The compressed data is written to an output file.

#### 4.2 **Decompression Process**

1. The user invokes the program with the command to decompress.
2. The program opens the compressed file and reads the encoded data.
3. The program reconstructs the Huffman tree from the file.
4. The program decodes the compressed data back to its original form using the Huffman tree.
5. The decompressed data is written to an output file.

### **5. Sample Interaction (CLI)**

**Compression:**

```sh
$ compress_tool -c input.txt output_compressed.bin
```

- The program will read `input.txt`, compress it, and save the result to `output_compressed.bin`.

**Decompression:**

```sh
$ compress_tool -d output_compressed.bin decompressed.txt
```

- The program will read `output_compressed.bin`, decompress it, and save the result to `decompressed.txt`.

---

### **6. Error Cases**

- If the input file does not exist, print an error and terminate the program.
- If the output file cannot be written, print an error and terminate the program.
- If the wrong operation mode is chosen, print the help message and terminate.

---

### **7. Performance Considerations**

- **Memory Usage**: Ensure that memory is freed after each operation (e.g., after building the Huffman tree).
- **Compression Efficiency**: The efficiency of the compression will depend on the algorithm chosen. Huffman coding is optimal for many types of data.
- **Speed**: Focus on minimizing I/O operations and optimizing the encoding/decoding process.

---

### **Conclusion**

This LLD outlines the design of a simple file compression tool in C, focusing on the modularity of file I/O, the compression algorithm, and user interaction. Each module works together to provide the core functionality of compressing and decompressing files while handling errors and user inputs gracefully.
