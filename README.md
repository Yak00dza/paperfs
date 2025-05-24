# paperfs
This is a half-joke project for storing files on physical paper with possibility of recovery.
As one might know, nowadays your files are never 100% safe from cyberthreats - except for when they are stored on paper in your drawer.

## Installation
`make` will compile and link the code. The `fprint` binary will appear in the cwd.

## What is the present functionality?
Right now this is a proof of concept version consisting of only one executable - `fprint`

## fprint
fprint takes a file as an input and convert it into a .pbm image for printing.
One takes this image and prints it to be 100% sure it is safely stored.  
Right now the maximum input file size is 744 bytes, but that can be changed with adjusting bar properties in `converts.h`.  
Splitting of larger files into several pages will be added later.

### Syntax
`fprint input_file.whatever output.pbm`
### Example
Below you can see a text file encoded on paper with `fprint`.
![example](https://github.com/user-attachments/assets/c83cbb93-422a-4beb-a45f-374915795f93)

## What are the future plans?
My ideas for developing this project include:
- Most importantly: retrieving data from scanned images
- Splitting larger files into pages
- Adding human-readoble identification data on page colontitles: file name, page number, hashsum of the content of the page for integity assurance.
- Compressing files before encoding them on paper and decompressing during retrieval
