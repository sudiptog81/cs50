# Questions

## What's `stdint.h`?

The `stdint.h` file is a header file that contains the definitions of various integer 'types' having specified widths. Usually, the `int` data type occupies 4-bytes i.e. 32-bits along with 1 sign-bit on the memory of most modern computers. We are using the particular header file in this problem set as integers do not occupy the same number of bytes in all systems, whereas the types as defined in this header file provides integers of fixed widths.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The `stdint.h` header defines various integer types having widths of 8-bits, 16-bits, 32-bits, etc. with their signed and unsigned alternatives. These keywords extend the definition of the standard `int` data type. 

The `uint8_t` type declares an unsigned integer of 8-bits (1-byte) used for fields of type `BYTE` as per the BMP file format specification. The `uint32_t` type declares an unsigned long integer of 32-bits (4-bytes) used for fields of type `DWORD`. The `int32_t` type declares a signed long integer of 32-bits (4-bytes) and used for fields of type `LONG`. The `uint16_t` declares an unsigned integer of 16-bits (2-bytes) used for fields of type `WORD`.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A `BYTE` is 1-byte, a `DWORD` is 4-bytes, a `LONG` is 4-bytes and a `WORD` is 2-bytes in size.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of any BMP file should be `42` and `4D` (`0x4d42` in hexadecimal or `BM` in ASCII). These are the leading bytes for identifying a bitmap image file.

## What's the difference between `bfSize` and `biSize`?

The difference between `bfSize` and `biSize` is that `bfSize` refers to the size of the `BITMAPFILEHEADER` structure and is equal to 14 bytes. On the other hand `biSize` refers to the size of the `BITMAPINFOHEADER` structure and is equal to 40 bytes.

## What does it mean if `biHeight` is negative?

Bitmap images normally contain a positive value of `biHeight` which indicates that the origin coordinate of the image is the lower-left corner.

When the value of `biHeight` is negative, it means that the particular bitmap file is a top-down bitmap file in which the order of rows is reversed i.e. the origin coordinate is the upper-left corner. A bitmap file with a negative value of `biHeight` cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The `biBitCount` field in the `BITMAPINFOHEADER` structure specifies the color depth i.e. bits per pixel, for a bitmap file. The value of `biBitCount` can be 0, 1, 4, 8, 16, 24 or 32.

## Why might `fopen` return `NULL` in `copy.c`?

The call to `fopen` returns a pointer to a `FILE` object when the filename as specified by the first parameter can be successfully opened in the mode as specified by the second argument in the function call. It returns `NULL` i.e. a null pointer in case the file cannot be opened in cases where the file does not exist or there is a permission error.

## Why is the third argument to `fread` always `1` in our code?

The third argument in the function call of `fread` is used to specify number of elements to read from the file of the size specified by the second argument. In our code, the argument is always `1` as we are reading a single element of a specified size in each function call.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The value that `copy.c` assigns to `padding` when `bi.biWidth` is `3` is calculated as `(4 - (3 * sizeof(RGBTRIPLE)) % 4) % 4 => (4 - (3 * 3) % 4) % 4 => (4 - 1 % 4) % 4 => 3 % 4 => 3` i.e. `3`.

## What does `fseek` do?

The `fseek` function sets the position indicator in the file as denoted by the file pointer in the first argument, to an offset as specified by the second argument, from the 'origin' position as denoted by the third argument.

## What is `SEEK_CUR`?

`SEEK_CUR` is a constant value that means 'current position of the file pointer'. It is a 'flag' that is used by the `fseek` function to determine the position from where offset is to be added.

`SEEK_CUR` is only used as an argument to the function and when used tells `fseek` to add the offset from the current position of the file pointer.
