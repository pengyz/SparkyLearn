#include "layer.h"

namespace sparky {
    namespace graphics {

        Layer::Layer(Renderer2D* render, Shader* shader, maths::mat4 matrix) :
            m_Renderer(render), m_Shader(shader), m_ProjectionMatrix(matrix)
        {
            m_Shader->enable();
            m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
        }


        Layer::~Layer()
        {
            m_Shader->disable();
            delete m_Shader;
            delete m_Renderer;

            for (auto renderable : m_Renderables)
                delete renderable;
        }


        void Layer::add(Renderable2D* renderable)
        {
            m_Renderables.push_back(renderable);
        }

        void Layer::render()
        {
            m_Renderer->begin();
            for (auto renderable : m_Renderables)
            {
                m_Renderer->submit(renderable);
            }
            m_Renderer->end();
            m_Renderer->flush();
        }

    }
}