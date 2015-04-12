//
//  face.cc
//  rpusbdispsdk
//
//  Created by Tony Huang on 12/26/13.
//  Copyright (c) 2013 RoboPeak.com. All rights reserved.
//

#include <rp/deps/freetype2_wrap/face.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;
using namespace rp::util;

namespace rp { namespace deps { namespace freetype2_wrap {
    
    class FaceImpl : public noncopyable {
    public:
        FaceImpl(FT_Face face) : face_(face) {}
        ~FaceImpl() {
            FT_Done_Face(face_);
            face_ = 0;
        }
        
        void setCharSize(float ptSize, unsigned int horizonResolution, unsigned int verticalResolution) {
            FT_Set_Char_Size(face_, 0, (unsigned int)(ptSize*64), horizonResolution, verticalResolution);
        }
        
    private:
        FT_Face face_;
    };
    
    Face::Face(void* face) : impl_(new FaceImpl(*reinterpret_cast<FT_Face*>(face))) {}
    Face::~Face() {}
    
    void Face::setCharSize(float ptSize, unsigned int horizonResolution, unsigned int verticalResolution) {
        impl_->setCharSize(ptSize, horizonResolution, verticalResolution);
    }
    
}}}
