// --------------------------------------------------
// -*- C -*- Compatibility Header
//
// Copyright (C) 2023 Developer Jarvis (Pen Name)
//
// This file is part of the [Project Name] Library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// [Project Name] - [brief description of what it does]
// 
// Author: Developer Jarvis (Pen Name)
// Contact: https://github.com/DeveloperJarvis
//
// --------------------------------------------------

// --------------------------------
// FCT: File Compress Tool  will compress and decompress files, primarily using algorithms like
// *Huffman Coding* or *Run-Length Encoding (RLE)*
// --------------------------------

// --------------------------------
// Header files and #define declarations
// --------------------------------

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum number of characters (for ASCII, 256)
#define MAX_CHARACTERS 256
#if defined (_MSC_VER)
#define FOPEN(fptr, filepath, mode) fopen_s(fptr, filepath, mode)
#else
#define FOPEN(fptr, filepath, mode) (fptr = fopen(filepath, mode))
#endif

// --------------------------------
// User Defined Data Structures
// --------------------------------

// Structure for Frequency Table Entry
typedef struct 
{
	char character;
	int frequency;
} freq_entry;

// Structure for Huffman Tree Node
typedef struct huffman_node 
{
	char character;
	int frequency;
	struct huffman_node *left, *right;
} huffman_node;

// Structure for Huffman Code Entry
typedef struct
{
	char character;
	char *code;
} huffman_code;

// Structure for Command-line Arguments
typedef struct
{
	char *input_file;
	char *output_file;
	bool is_compress;
} command_line_args;

// --------------------------------
// Forward function declarations/ prototypes
// --------------------------------

// display help and version
void display_help(char *arg);
void display_version(char *arg);

// parsing commmand line arguments
void parse_command_line_arguments(int argc, char *argv[], command_line_args *args);

// File I/O Handling
FILE *open_file(const char *filepath, const char *mode);
int read_file(FILE *fptr, void *buffer, size_t size);
int write_file(FILE *fptr, const void *buffer, size_t size);
void close_file(FILE *fptr);

// Compression/ Descompression Algorithm
// Compression
void build_frequency_table(const char *file_data, freq_entry *table, int *size);
huffman_node *build_huffman_tree(const freq_entry *table, int size);
void generate_huffman_codes(huffman_node *root, char *code, int length, huffman_code *codes, int *index);
void compress_data(const char *file_data, const huffman_code *codes, char *compressed_data, int *compressed_size);
// Decompression
//void decode_data(const char *compressed_data, int compressed_size);
//void build_huffman_tree_from_file(char *file_data);
void decompress_data(const char *compressed_data, int compressed_size, huffman_node *root, char *decompressed_data);

// free tree and other data
void free_huffman_tree(huffman_node *root);
void free_huffman_codes(huffman_code *codes, int size);

int main(int argc, char *argv[])
{
	command_line_args args;
	parse_command_line_arguments(argc, argv, &args);
	
	// Open input file
	FILE *input_file = open_file(args.input_file, "rb");
	
	// Read the entire file into memory
	fseek(input_file, 0, SEEK_END);
	long file_size = ftell(input_file);
	fseek(input_file, 0, SEEK_SET);

	char *file_data = (char *)malloc(file_size);
	if (file_data == NULL)
	{
		perror("Error allocating memory for file data");
		exit(1);
	}
	read_file(input_file, file_data, file_size);
	close_file(input_file);

	if (args.is_compress)
	{
		// Compression
		freq_entry freq_table[MAX_CHARACTERS];
		int freq_size = 0;
		build_frequency_table(file_data, freq_table, &freq_size);

		huffman_node *root = build_huffman_tree(freq_table, freq_size);
		huffman_code *codes = (huffman_code *)malloc(sizeof(huffman_code) * freq_size);
		int code_index = 0;
		generate_huffman_codes(root, "", 0, codes, &code_index);

		char *compressed_data = (char *)malloc(file_size);	// This is an estimation, could be optimized
		int compressed_size = 0;
		compress_data(file_data, codes, compressed_data, &compressed_size);

		// Write comressed data to output file
		FILE *output_file = open_file(args.output_file, "wb");
		write_file(output_file, compressed_data, compressed_size);
		close_file(output_file);

		// Free memory
		free_huffman_tree(root);
		free_huffman_codes(codes, code_index);
		free(file_data);
		free(compressed_data);
	}
	else
	{
		// Decompression
		// For now, we'll assume a trivial decompression (real-world scenario would store tree info)
		// Decompression would require rebuilding the Huffman tree from the compressed data
		FILE *output_file = open_file(args.output_file, "wb");
		// Implement decompression here based on the compressed file's structure
		// Placeholder, needs proper tree reconstruction from compressed file format
		close_file(output_file);
	}

	return 0;
}


// --------------------------------
// Function Definitions
// --------------------------------

void display_help(char *arg)
{
	printf("List of options\n");
	printf(" -h --help		display help\n");
	printf(" -v --version		display version\n");
	printf("Usage for file preocessing: \n");
	printf("%s [-otions] <input_file> <output_file>\n", arg);
	printf(" -c --compress		for compression\n");
	printf(" -d --decompress	for decompression\n");
}

void display_version(char *arg)
{
	printf("%s version: 1.0.0\n", arg);
}

void parse_command_line_arguments(int argc, char *argv[], command_line_args *args)
{
	if (argc < 4)
	{
		if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
		{
			display_help(argv[0]);
			exit(0);
		}
		else if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
		{
			display_version(argv[0]);
			exit(0);
		}
		else
		{
			display_help(argv[0]);
			exit(1);
		}
	}

	args->is_compress = false;
	if (strcmp(argv[1], "-c") == 0)
	{
		args->is_compress = true;
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		args->is_compress = false;
	}
	else
	{
		display_help(argv[0]);
		exit(1);
	}

	args->input_file = argv[2];
	args->output_file = argv[3];
}


FILE *open_file(const char *filepath, const char *mode)
{
	FILE *fptr;
	FOPEN(fptr, filepath, mode);
	if (fptr == NULL)
	{
		perror("Error opening file\n");
		exit(1);
	}
	return fptr;
}

int read_file(FILE *fptr, void *buffer, size_t size)
{
	size_t bytes_read = fread(buffer, 1, size, fptr);
	if (bytes_read != size)
	{
		perror("Error reading file\n");
		exit(1);
	}
	return bytes_read;
}

int write_file(FILE *fptr, const void *buffer, size_t size)
{
	size_t bytes_written = fwrite(buffer, 1, size, fptr);
	if (bytes_written != size)
	{
		perror("Error writing file\n");
		exit(1);
	}
	return bytes_written;
}

void close_file(FILE *fptr)
{
	fclose(fptr);
}

// Helper function to build frequency table from input data
void build_frequency_table(const char *file_data, freq_entry *table, int *size)
{
	int freq[MAX_CHARACTERS] = {0};
	for (int i = 0; file_data[i] != '\0'; i++)
	{
		freq[(unsigned char)file_data[i]]++;
	}
	for (int i = 0; i < MAX_CHARACTERS; i++)
	{
		if (freq[i] > 0)
		{
			table[*size].character = (char)i;
			table[*size].frequency = freq[i];
			(*size)++;
		}
	}
}

// Helper function to build a Huffman tree
huffman_node *build_huffman_tree(const freq_entry *table, int size)
{
	// Simplified version
	// Use a min-heap or priority queue to build the tree
	// This is a simplified placeholder
	huffman_node *root = (huffman_node *)malloc(sizeof(huffman_node));
	root->character = table[0].character;
	root->frequency = table[0].frequency;
	root->left = root->right = NULL;
	
	for (int i = 0; i < size; i++) 
	{
		// process table[i] as needed
	}

	return root;
}

// Helper function to generate Huffman codes
void generate_huffman_codes(huffman_node *root, char *code, int length, huffman_code *codes, int *index)
{
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
	{
		codes[*index].character = root->character;
		codes[*index].code = (char *)malloc(length + 1);
		strncpy(codes[*index].code, code, length);
		codes[*index].code[length] = '\0';
		(*index)++;
	}

	if (root->left)
	{
		code[length] = '0';
		generate_huffman_codes(root->left, code, length + 1, codes, index);
	}
	if (root->right)
	{
		code[length] = '1';
		generate_huffman_codes(root->right, code, length + 1, codes, index);
	}
}

// Placeholder for compressing data
void compress_data(const char *file_data, const huffman_code *codes, char *compressed_data, int *compressed_size)
{
	// Implemented compression logic using Huffman codes
	// This is a simplified placeholder for actual bit manipulation
	unsigned char *bit_stream = (unsigned char *)malloc(MAX_CHARACTERS * sizeof(unsigned char));	// Allocate memory for the bitstream
	if (bit_stream == NULL)
	{
		perror("Error allocating memory for bitstream");
		exit(1);
	}
	int bit_index = 0;

	for (int i = 0; file_data[i] != '\0'; i++)
	{
		for (int j = 0; j < MAX_CHARACTERS; j++)
		{
			if (codes[j].character == file_data[i])
			{
				// Store the Huffman code for the character (bit-level manipulation required)
				//strcat(compressed_data, codes[j].code);
				for (int k = 0; codes[j].code[k] != '\0'; k++)
				{
					bit_stream[bit_index/ 8] |= (1 << (7 -(bit_index % 8)));	// Set the bit to 1
				}
				bit_index++;
			}
		}
	}
	// Calculate the final size (in bytes) for the compressed data
	//*compressed_size = strlen(compressed_data);
	*compressed_size = (bit_index + 7) / 8;

	// Covert the bit steam back to a byte array (if needed) to be written to a file
	memcpy(compressed_data, bit_stream, *compressed_size);

	free(bit_stream);	// Free the allocated memory
}

// Placeholder for decompressing data
void decompress_data(const char *compressed_data, int compressed_size, huffman_node *root, char *decompressed_data)
{
	// Implement decompression logic using Huffman tree
	// This is a simplified placeholder for actual bit-level manipulation
	(void)compressed_data;		// Mark unused
	(void)compressed_size;		// Mark unused
	(void)root;			// Mark unused
	(void)decompressed_data;	// Mark unused
}


// Free allocated memory for Huffman Tree
void free_huffman_tree(huffman_node *root)
{
	if (root == NULL)
		return;
	free_huffman_tree(root->left);
	free_huffman_tree(root->right);
	free(root);
}

// Free allocated memory for Huffman codes
void free_huffman_codes(huffman_code *codes, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(codes[i].code);
	}
	free(codes);
}

