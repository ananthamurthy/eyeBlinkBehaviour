/*
 * =====================================================================================
 *
 *       Filename:  TiffWriter.hpp
 *
 *    Description:  A class to write tiff files.
 *
 *        Version:  1.0
 *        Created:  Saturday 03 December 2016 10:31:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include <string>
#include <tiffio.h>
 
class TiffWriter
{
public:
    TiffWriter(std::string filename, bool multiPage);
    TiffWriter(const TiffWriter&) = delete;
    TiffWriter& operator=(const TiffWriter&) = delete;
    ~TiffWriter();
     
    void write(const unsigned char* buffer, int width, int height);
 
private:
    TIFF* tiff;
    bool multiPage;
    unsigned int page;
};
 
TiffWriter::TiffWriter(std::string filename, bool multiPage) : page(0), multiPage(multiPage)
{
    tiff = TIFFOpen(filename.c_str(), "w");
}
 
void TiffWriter::write(const unsigned char* buffer, int width, int height)
{
    if (multiPage) {
        /*
         * I seriously don't know if this is supposed to be supported by the format,
         * but it's the only we way can write the page number without knowing the
         * final number of pages in advance.
         */
        TIFFSetField(tiff, TIFFTAG_PAGENUMBER, page, page);
        TIFFSetField(tiff, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);
    }
    TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
    TIFFSetField(tiff, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tiff, (unsigned int) - 1));
 
    unsigned int samples_per_pixel = 1;
    unsigned int bits_per_sample = 8;
    TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, bits_per_sample);
    TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, samples_per_pixel);
 
    std::size_t stride = width;
    for (unsigned int y = 0; y < height; ++y) {
        TIFFWriteScanline(tiff, buf + y * stride, y, 0);
    }
 
    TIFFWriteDirectory(tiff);
    page++;
}
 
TiffWriter::~TiffWriter()
{
    TIFFClose(tiff);
}
