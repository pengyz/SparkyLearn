#pragma once
#include <string>
#include <FreeImage.h>
#include <GL/glew.h>



namespace sparky {

    static BYTE* load_image(const char* path, GLsizei* width, GLsizei* height)
    {
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP *dib = nullptr;
        BYTE* bits = nullptr;
        *width = 0;
        *height = 0;
        GLuint gl_texID;

        fif = FreeImage_GetFileType(path, 0);
        if (fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(path);
        if (fif == FIF_UNKNOWN)
            return nullptr;

        if (FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, path);
        if (!dib)
            return nullptr;

        bits = FreeImage_GetBits(dib);
        *width = FreeImage_GetWidth(dib);
        *height = FreeImage_GetHeight(dib);

        return bits;
    }

}
