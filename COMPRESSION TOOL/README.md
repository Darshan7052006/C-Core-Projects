# 📦 File Compression Tool (RLE)

> A menu-driven file compression and decompression utility written in C using the **Run-Length Encoding (RLE)** algorithm.

This project compresses files by replacing repeated bytes with a count and value pair. It demonstrates binary file handling, file compression algorithms, integrity verification, compression statistics, history logging, and timestamp management.

---

# 🚀 Features

✅ Compress files using Run-Length Encoding (RLE)

✅ Decompress compressed files back to their original form

✅ Display compressed binary data in hexadecimal format

✅ Display decompressed file contents

✅ Verify integrity by comparing original and decompressed files

✅ Generate compression statistics

✅ Store compression history with timestamps

✅ View previously generated compression records

✅ Handle both text files and binary files

---

# 📖 How RLE Compression Works

RLE stores repeated data as:

```text
[count][character]
```

### Example

Original File:

```text
AAAAABBBBCC
```

Compressed Representation:

```text
5A4B2C
```

Internally Stored As:

```text
[5][A]
[4][B]
[2][C]
```

This reduces storage when large sequences of identical characters exist.

---

# 🖥️ Program Menu

```text
======== MENU ========

1. Compress File
2. Display Compressed File
3. Decompress File
4. Display Decompressed File
5. Integrity Verification
6. View History
7. Exit
```

---

# 📊 Compression Statistics

The program displays:

```text
File Size : 1000 Bytes
Compressed File Size : 300 Bytes
Total Bytes Saved : 700 Bytes
Compression Ratio : 3.33
Compression Percentage : 70.00%
```

---

# 🔍 Integrity Verification

After decompression, the program compares:

```text
Original File
      ↓
Decompressed File
```

Byte by byte.

Successful output:

```text
Verification Successful.
Both the original file and decompressed file are identical.
```

This ensures no data was lost during compression and decompression.

---

# 📝 History Logging

Each compression operation is stored in:

```text
History.txt
```

Example:

```text
HISTORY
=======================

Date : Tue Jun 09 18:25:42 2026

File Name : sample.txt
File Size : 1000 Bytes
Compressed File Size : 300 Bytes
Total Bytes Saved : 700 Bytes
Compression Ratio : 3.33
Compression Percentage : 70.00%

=======================
```

---

# 📂 Generated Files

| File             | Purpose                       |
| ---------------- | ----------------------------- |
| Compressed.bin   | Stores compressed binary data |
| Decompressed.txt | Stores decompressed output    |
| History.txt      | Stores compression history    |

---

# ⚙️ Supported File Types

The program operates on raw bytes using binary file I/O:

```c
fopen(filename, "rb");
fread(...);
fwrite(...);
```

Because of this, it can process:

✅ Text files

✅ Binary files

✅ Data files

✅ Images (as raw bytes)

✅ Any file that can be read byte-by-byte

---

# ⚠️ Important Note About Compression

RLE does **not always reduce file size**.

It performs best when there are long runs of repeated characters.

### Good Example

Input:

```text
AAAAAAAAAA
```

Original Size:

```text
10 Bytes
```

Compressed Size:

```text
2 Bytes
```

Excellent compression.

---

### Poor Example

Input:

```text
A
```

Original Size:

```text
1 Byte
```

Compressed Size:

```text
2 Bytes
```

Why?

Because the compressed format stores:

```text
[Count][Character]
```

which requires:

```text
1 Byte + 1 Byte = 2 Bytes
```

This is expected behavior and demonstrates one of the limitations of Run-Length Encoding.

---

# 🔢 Why Is The Maximum Count 255?

The compression counter is stored as:

```c
unsigned char count;
```

An unsigned char occupies 1 byte (8 bits).

Maximum value:

```text
255
```

Therefore the largest run that can be stored directly is:

```text
255A
```

If a character repeats more than 255 times:

```text
300 A's
```

it is automatically split into:

```text
255A
45A
```

During decompression:

```text
255 + 45 = 300
```

so no information is lost.

---

# 🛠️ Technologies Used

* C Programming
* File Handling
* Binary File Processing
* Text File Processing
* Run-Length Encoding (RLE)
* Error Handling
* Time Library (`time.h`)
* Modular Programming

---

# 🧪 Testing Performed

The project was tested using:

✅ Empty files

✅ Single-character files

✅ Files with repeated characters

✅ Files with no repetition

✅ Mixed-character files

✅ Integrity verification checks

✅ Compression history logging

---

# 🎯 Learning Outcomes

Through this project I learned:

* Binary file handling
* Text file handling
* Compression algorithms
* Data encoding and decoding
* File integrity verification
* Statistics generation
* History logging
* Timestamp handling
* Error handling
* Debugging and testing
* Modular program design

---

# ⚙️ Compilation

Compile using GCC:

```bash
gcc compression_tool.c -o compression_tool
```

Run:

```bash
./compression_tool
```

---

# 👨‍💻 Author

**Darshan**

Built as part of my C Programming Portfolio to strengthen programming fundamentals and prepare for Embedded Systems Development.
