#pragma once
#include "renderable2d.h"

namespace sparky {
    namespace graphics {
        class Renderer2D {
        protected:
            std::vector<maths::mat4> m_TransformationStack;
            Renderer2D() {
                m_TransformationStack.push_back(maths::mat4::identity());
            }
        public:
            void push(const maths::mat4& matrix, bool bOverride = false)
            {
                if (bOverride)
                {
                    m_TransformationStack.push_back(matrix);
                }
                else
                {
                    m_TransformationStack.push_back(matrix * m_TransformationStack.back());
                }
            }

            void pop()
            {
                if (m_TransformationStack.size() > 1)
                {
                    m_TransformationStack.pop_back();
                }
                //TODO: Add to log!
            }


            virtual void submit(Renderable2D* renderable) = 0;
            virtual void flush() = 0;
            virtual void begin() {}
            virtual void end() {}
        };
    }
}