//
//  context.cc
//  rpusbdispsdk
//
//  Created by Tony Huang on 12/26/13.
//  Copyright (c) 2013 RoboPeak.com. All rights reserved.
//

#include <rp/deps/freetype2_wrap/context.h>
#include <rp/deps/freetype2_wrap/face.h>
#include <rp/util/exception.h>
#include <ft2build.h>
#include <mutex>
#include FT_FREETYPE_H

using namespace std;
using namespace rp::util;

namespace rp { namespace deps { namespace freetype2_wrap {
    
    class ContextImpl {
    public:
        ContextImpl() {
            int error = FT_Init_FreeType(&library_);
            if (error) {
                throw new Exception(error);
            }
        }
        
        ~ContextImpl() {
            FT_Done_FreeType(library_);
            library_ = 0;
        }
        
        shared_ptr<Face> openFace(const string& path, int faceIndex) {
            FT_Face face;
            
            int error = FT_New_Face(library_, path.c_str(), faceIndex, &face);
            
            if (error) {
                throw new Exception(error);
            }
            
            return shared_ptr<Face>(new Face(&face));
        }
        
    private:
        FT_Library library_;
    };
    
    static once_flag onceFlag_;
    static shared_ptr<Context> defaultContext_;
    
    Context::Context() : impl_(new ContextImpl()) {}
    Context::~Context() {}
    
    shared_ptr<Face> Context::openFace(const std::string &path, int faceIndex) {
        return impl_->openFace(path, faceIndex);
    }
    
    shared_ptr<Context> Context::defaultContext() {
        call_once(onceFlag_, []() { defaultContext_ = shared_ptr<Context>(new Context()); });
        return defaultContext_;
    }
    
}}}
