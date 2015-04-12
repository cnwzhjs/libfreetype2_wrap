//
//  context.h
//  rpusbdispsdk
//
//  Created by Tony Huang on 12/26/13.
//  Copyright (c) 2013 RoboPeak.com. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <rp/util/noncopyable.h>

namespace rp { namespace deps { namespace freetype2_wrap {

    class ContextImpl;
    class Face;
    
    class Context : public rp::util::noncopyable {
    public:
        ~Context();
        
        std::shared_ptr<Face> openFace(const std::string& path, int faceIndex = 0);
        
        static std::shared_ptr<Context> defaultContext();
        
    private:
        Context();
        
        std::unique_ptr<ContextImpl> impl_;
    };
    
}}}
