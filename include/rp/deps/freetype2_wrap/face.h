//
//  face.h
//  rpusbdispsdk
//
//  Created by Tony Huang on 12/26/13.
//  Copyright (c) 2013 RoboPeak.com. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <rp/util/noncopyable.h>
#include <rp/util/utf8.h>

namespace rp { namespace deps { namespace freetype2_wrap {
    
    class ContextImpl;
    class FaceImpl;
    
    class Face : public rp::util::noncopyable {
    public:
        ~Face();
        
        void setCharSize(float ptSize, unsigned int horizonResolution = 72, unsigned int verticalResolution = 72);
        
        int getCharIndex(uint32_t c);
        void loadGlyph(int glyphIndex);
    private:
        friend class ContextImpl;

        Face(void* face);
        
        std::unique_ptr<FaceImpl> impl_;
    };
    
}}}

