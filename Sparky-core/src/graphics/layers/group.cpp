#include "group.h"
#include "../renderer2d.h"


namespace sparky {
    namespace graphics {
        Group::Group(const maths::mat4& transform) :
            m_TransformationMatrix(transform)
        {

        }

        Group::~Group()
        {
        }

        void Group::submit(Renderer2D * renderer) const
        {
            renderer->push(m_TransformationMatrix);
            for (auto renderable : m_Renderables)
                renderable->submit(renderer);
            renderer->pop();
        }


        void Group::add(Renderable2D* renderable) {
            m_Renderables.push_back(renderable);
        }


    }
}