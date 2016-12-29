#pragma once
#include "layer.h"

namespace sparky {
    namespace graphics {


        class TileLayer :public Layer
        {
        public:
            TileLayer(Shader* shader);
            ~TileLayer();
        };
    }
}