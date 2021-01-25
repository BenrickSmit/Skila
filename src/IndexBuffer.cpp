#include "IndexBuffer.h"  
#include "Renderer.h"
#include "GL/glew.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):
    m_count(count) {
    std::cerr << "unsigned int size: " << sizeof(unsigned int) << std::endl;
    std::cerr << "GLuint size: " << sizeof(GLuint) << std::endl;
    

    GLCall(glGenBuffers(1, &m_renderer_id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int) , data, GL_DYNAMIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline unsigned IndexBuffer::get_count() const {
    return m_count;
}