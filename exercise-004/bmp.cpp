#include "bmp.h"
#include <fstream>
#include <fmt/format.h>
#include <vector>
#include <iostream>

template<typename T> // mit dem T ist es egal welcher Datentyp vorliegt
static void read_value(std::fstream& file,T* value )
{
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

// Funktion zur Darstellung des Graustufenvektors als ASCII-Bild
void displayAsciiImage(const std::vector<uint8_t>& grey_buffer, int width, int height) {
    // Zeichen zur Darstellung der Graustufen (hier einfach gehalten)
    const std::string ascii_chars = " .:-+*#%@"; // @%#*+=-:.
    
    // Schleife über den Graustufenvektor
    for (int j = 0; j < height; j++){   //for-Schleife über die Hoehe des Bildes

        for (int i = 0; i < width; ++i) {   //for-Schleife über die Breite des Bildes        // ASCII-Charakter basierend auf dem Grauwert
            int index = grey_buffer[i+(height-j)*width] * (ascii_chars.size() - 1) / 255; // height-j dreht das Bild
            //int index = grey_buffer[i+j*width] * (ascii_chars.size() - 1) / 255; hier steht das bild auf dem Kop
            char ascii_char = ascii_chars[index];
            
            // Ausgabe des ASCII-Zeichens
            std::cout << ascii_char;
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

    int width_len = info_header.biWidth*3;  // mal drei, wegen den drei Pixelfarben
    int padding_len = 4-width_len%4;        // modulo 4 gibt den Rest, das 4-%4 beschreibt die auffülbits um eine durch 4teilbare Zahl zu bekommen
    fmt::println("padding Laenge: {}", padding_len);
    
    for(int j = 0; j <info_header.biHeight; j++){
        for(int i = 0; i < info_header.biWidth; i++ ){
            // Speichern der Werte in den pixelbuffer
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].red);         // Spalte + die durchgelaufenen Spalten
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].green);
            read_value(input_file, &pixel_buffer[i+j*info_header.biWidth].blue);           
        }
        // SChreiben der Paddingwerte einer Zeile in den Trash, die ueberschuessigen 1-3 Werte
        for (int x=0; x < padding_len; x++ ){
            read_value(input_file, &pixel_buffer[j].trash);
        }        
    }
    std::vector<uint8_t> grey_buffer(buffer_size);
    for(int j = 0; j< buffer_size; j++)
    {
        // hier wird der gefüllte Pixelbuffer über die Funktion grey zu einem Grauwert umgerechnet
        grey_buffer[j] = pixel_buffer[j].grey(); // die funktion grey() funktioniert ohne Eingabewerte, weil sie rot,grün und blau aus der Klasse kennt
    }
    // grey_buffer enthält für jeden Pixel einen Wert zw. 0-255 für den Grauwert
    //fmt::println("länge grey_buffer: {}", size(grey_buffer));
    //fmt::println("grey_buffer 1: {}", grey_buffer[10000]);
    displayAsciiImage(grey_buffer,info_header.biWidth, info_header.biHeight);
    return ret; 
}




