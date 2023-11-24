#include "bmp.h"
#include <fstream>
#include <fmt/format.h>
#include <vector>
#include <iostream>

template<typename T>
static void read_value(std::fstream& file,T* value )
{
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

// Funktion zur Darstellung des Graustufenvektors als ASCII-Bild
void displayAsciiImage(const std::vector<uint8_t>& grey_buffer, int width, int height) {
    // Zeichen zur Darstellung der Graustufen (hier einfach gehalten)
    const std::string ascii_chars = "@%#*+=-:. ";
    
    // Schleife über den Graustufenvektor
    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; ++i) {
        // Bestimme den entsprechenden ASCII-Charakter basierend auf dem Grauwert
        int index = grey_buffer[i+(height-j)*width] * (ascii_chars.size() - 1) / 255;
        char ascii_char = ascii_chars[index];
        
        // Ausgabe des ASCII-Zeichens
        std::cout << ascii_char;
        
        /*// Zeilenumbruch nach jeder Zeile entsprechend der Bildbreite
        if ((i + 1) % width == 0) {
        }*/
    }
            std::cout << std::endl;
    }
    
}

// Definition der Funktion function1
bool BMP::read(const std::string& filename) {
    // open a file in read mode.
    auto ret = false; 
    
    std::fstream input_file(filename, std::ios::binary | std::ios::in); 
    if (!input_file.is_open()) {
        fmt::print("Unable to open the file: {}\n",filename);
        return ret;
    }
    BITMAPFILEHEADER file_header;
    read_value(input_file,&file_header.bfType);
    read_value(input_file,&file_header.bfSize);
    read_value(input_file,&file_header.bfReserved);
    read_value(input_file,&file_header.bfOffBits);

    BITMAPINFOHEADER info_header;
    read_value(input_file,&info_header.biSize);
    read_value(input_file,&info_header.biWidth);
    read_value(input_file,&info_header.biHeight);
    read_value(input_file,&info_header.biPlanes);
    read_value(input_file,&info_header.biBitCount);
    read_value(input_file,&info_header.biCompression);
    read_value(input_file,&info_header.biSizeImage);
    read_value(input_file,&info_header.biXPelsPerMeter);
    read_value(input_file,&info_header.biYPelsPerMeter);
    read_value(input_file,&info_header.biClrUsed);
    read_value(input_file,&info_header.biClrImportant);

    fmt::println("Type: {}", file_header.bfType);
    fmt::println("Size Header: {}", file_header.bfSize);
    fmt::println("Bits: {}", file_header.bfOffBits);
    fmt::println("Reserved: {}", file_header.bfReserved);
    fmt::println("Width: {}", info_header.biWidth);
    fmt::println("Height: {}", info_header.biHeight);
    fmt::println("BitCount: {}", info_header.biBitCount);
    fmt::println("ClrImportant: {}", info_header.biClrImportant);
    fmt::println("ClrUsed: {}", info_header.biClrUsed);
    fmt::println("Compression: {}", info_header.biCompression);
    fmt::println("Planes: {}", info_header.biPlanes);
    fmt::println("Size Info: {}", info_header.biSize);
    fmt::println("SizeImage: {}", info_header.biSizeImage);
    fmt::println("XPelsPerMeter: {}", info_header.biXPelsPerMeter);
    fmt::println("YPelsPerMeter: {}", info_header.biYPelsPerMeter);

    int buffer_size = info_header.biWidth*info_header.biHeight; //Breite mal Höhe aus dem Bild
    fmt::println("Buffer Size {}", buffer_size);
    std::vector<pixel> pixel_buffer(buffer_size);
    int width_len = info_header.biWidth*3;
    int padding_len = 4- width_len%4;
    
    for(int j = 0; j <info_header.biHeight; j++){
        for(int i = 0; i < info_header.biWidth; i++ ){
            //uint8_t padding = 0;
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].red);
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].green);
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].blue);           
            //input_file >> padding;
        }
        for (int x=0; x < padding_len; x++ ){
            input_file >> pixel_buffer[j].alpha;
        }        
    }
    std::vector<uint8_t> grey_buffer(buffer_size);
    for(int j = 0; j< buffer_size; j++)
    {
        grey_buffer[j] = pixel_buffer[j].grey();
    }
    displayAsciiImage(grey_buffer,info_header.biWidth, info_header.biHeight);
    return ret;

    /*for (int i = 0; i<buffer_size; i++){
        fmt::println("Grey Buffer {}", grey_buffer[i]);
    }*/
    
  
}

// Definition der Funktion function2
bool BMP::write(const std::string& filename) {
    auto ret = false;
    std::ifstream infile;
    //std::cout << "Reading from the file" << std::endl; 
    //infile >> data; 
    //cout << data << endl;
    return ret;
}



/*void BMP::BitmapFileHeader::print()
{
fmt::println("Bitmap File Info Header:");
fmt::println("The start {}{}", bfType[0], bfType[1];)

}*/
