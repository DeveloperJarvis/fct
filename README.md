# FCT: File Compression Tool

A simple file compression and decompression tool written in C, utilizing algorithms like **Huffman Coding** or **Run-Length Encoding (RLE)**. This tool allows you to compress files to reduce their size and decompress them back to their original state.

---

## Features

- **Compression**: Compress files using efficient algorithms like Huffman Coding.
- **Decompression**: Restore the compressed files to their original form.
- **CLI Interface**: Simple command-line interface for easy usage.
- **Error Handling**: Handles common errors such as invalid files, unsupported formats, and incorrect command-line arguments.

---

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)

   - [Compressing a File](#compressing-a-file)
   - [Decompressing a File](#decompressing-a-file)

3. [Building the Project](#building-the-project)
4. [Supported Compression Algorithms](#supported-compression-algorithms)
5. [Error Handling](#error-handling)
6. [License](#license)

---

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/DeveloperJarvis/fct.git
   cd fct
   ```

2. **Dependencies**:

   No external dependencies are required for this project as it is implemented in pure C.

3. **Build the Project**:

   Compile the C source code using `gcc` or any other C compiler:

   ```bash
   gcc -o fct fct.c
   ```

4. After successful compilation, the `fct` executable will be created in the project directory.

---

## Usage

### Compressing a File

To compress a file, use the following command:

```bash
$ fct -c <input_file> <output_compressed_file>
```

- `-c`: Compress mode.
- `<input_file>`: Path to the input file that you want to compress.
- `<output_compressed_file>`: Path where the compressed file will be saved.

**Example:**

```bash
$ fct -c input.txt compressed.bin
```

This will compress `input.txt` and save the compressed file as `compressed.bin`.

### Decompressing a File

To decompress a file, use the following command:

```bash
$ fct -d <input_compressed_file> <output_file>
```

- `-d`: Decompress mode.
- `<input_compressed_file>`: Path to the compressed file that you want to decompress.
- `<output_file>`: Path where the decompressed file will be saved.

**Example:**

```bash
$ fct -d compressed.bin decompressed.txt
```

This will decompress `compressed.bin` and save the decompressed data as `decompressed.txt`.

---

## Building the Project

1. Clone the repository or download the source code.

2. Open the terminal in the project directory.

3. Run the following command to compile the code:

   ```bash
   gcc -o fct fct.c
   ```

4. After compilation, you should have an executable file `fct` in the directory.

---

## Supported Compression Algorithms

Currently, the tool supports the following compression algorithms:

1. **Huffman Coding**: A lossless data compression algorithm that assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters.
2. **Run-Length Encoding (RLE)**: A simple compression technique where sequences of the same data value are stored as a single value and count.

You can easily extend the tool to support other algorithms by modifying the core compression and decompression functions.

---

## Error Handling

The tool handles the following errors:

- **File Not Found**: If the input file cannot be found, an error message will be displayed.
- **Invalid File Format**: If the input file is not compatible with the tool, it will display an error.
- **Incorrect Command Usage**: If the user enters incorrect or missing arguments, a help message will be shown with usage instructions.

---

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.

---

## Contributing

If you'd like to contribute to this project, feel free to fork the repository, make improvements, and submit pull requests.

---

### Example Interaction

**Compression:**

```bash
$ fct -c input.txt compressed.bin
Compression successful. Output saved as compressed.bin
```

**Decompression:**

```bash
$ fct -d compressed.bin decompressed.txt
Decompression successful. Output saved as decompressed.txt
```

---

### Acknowledgments

- The tool utilizes the **Huffman Coding** and **Run-Length Encoding (RLE)** algorithms for file compression.
- Thanks to the C programming community for open-source tools and libraries.

## Creating tag

```bash
# 1. Check existing tags
git tag
# 2. Create a valid tag
git tag -a v1.0.0 -m "Release version 1.0.0"
# or lightweight tag
git tag v1.0.0
# push tag to remote
git push origin v1.0.0
```

-
