#include "bmp.h"
#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <vector>


// Definition der Funktion function1
bool BMP::read(const std::string& filename) {
    // open a file in read mode.
    auto ret = false;
    std::ifstream infile; 
    infile.open(filename); 
    BITMAPFILEHEADER file_header;
    infile >> file_header.bfType;
    infile >> file_header.bfSize;
    infile >> file_header.bfReserved;
    infile >> file_header.bfOffBits;
    BITMAPINFOHEADER info_header;
    infile >> info_header.biSize;
    infile >> info_header.biWidth;
    infile >> info_header.biHeight;
    infile >> info_header.biPlanes;
    infile >> info_header.biBitCount;
    infile >> info_header.biCompression;
    infile >> info_header.biSizeImage;
    infile >> info_header.biXPelsPerMeter;
    infile >> info_header.biYPelsPerMeter;
    infile >> info_header.biClrUsed;
    infile >> info_header.biClrImportant;

    int buffer_size = info_header.biWidth*info_header.biHeight; //Breite mal Höhe aus dem Bild
    std::vector<pixel> pixel_buffer(buffer_size);
    for(int i; i < buffer_size+1; i++ ){
        infile >> pixel_buffer[i].red;
        infile >> pixel_buffer[i].green;
        infile >> pixel_buffer[i].blue;
    }

   if (infile.is_open()) { 
        // was will ich hier machen?
        infile.close(); // Schließe die Datei nach dem Lesen
        return true; // Rückgabewert true, wenn das Lesen erfolgreich war
    } else {
        fmt::format("Einlesen fehlgeschlagen");
        return false; // Rückgabewert false, wenn das Lesen fehlgeschlagen ist
    }
   return ret;
  
}

// Definition der Funktion function2
bool BMP::write(const std::string& filename) {
    auto ret = false;
    std::ifstream infile;
    std::cout << "Reading from the file" << std::endl; 
    //infile >> data; 
    //cout << data << endl;
    return ret;
}
