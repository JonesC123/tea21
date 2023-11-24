#ifndef WORKSPACES_TEA21_EXERCISE_004_BMP_H
#define WORKSPACES_TEA21_EXERCISE_004_BMP_H

#include <string>
#include <vector>

class BMP {
    public:
        bool read(const std::string&  filename);
        //bool write(const std::string&  filename);
        //void displayAsciiImage(const std::vector<uint8_t>& grey_buffer, int width);
    private:  
        struct BITMAPFILEHEADER {
            uint16_t bfType;        // Dateityp-Kennung (z.B. 'BM' für Windows-Bitmap)
            uint32_t bfSize;        // Dateigröße in Bytes
            uint32_t bfReserved;   // Reserviert; sollte auf 0 gesetzt sein
            uint32_t bfOffBits;     // Offset zum Beginn der Bilddaten
        };
        struct BITMAPINFOHEADER {
            uint32_t biSize;          // Größe des Headers
            int32_t biWidth;         // Breite des Bildes in Pixeln
            int32_t biHeight;        // Höhe des Bildes in Pixeln
            int16_t biPlanes;        // Anzahl der Farbebenen (normalerweise 1)
            int16_t biBitCount;      // Anzahl der Bits pro Pixel
            int32_t biCompression;   // Komprimierungsmethode
            int32_t biSizeImage;     // Größe der Bilddaten in Bytes
            int32_t biXPelsPerMeter; // Anzahl der Pixel pro Meter in X-Richtung
            int32_t biYPelsPerMeter; // Anzahl der Pixel pro Meter in Y-Richtung
            int32_t biClrUsed;       // Anzahl der tatsächlich verwendeten Farben
            int32_t biClrImportant;  // Anzahl der wichtigen Farben
        };
        struct pixel
        {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            uint8_t trash;
            uint8_t grey(){
                return (pixel::red +pixel::green +pixel::blue)/3;
            }
        };
};
#endif