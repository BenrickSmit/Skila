#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#pragma once
	
class VertexBuffer  
{
	public:

		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind();
		void unbind();

	private:
		// OpenGL needs this as a type of ID for everything it creats
		// It's rendered_id, however, to keep it generic
		unsigned int m_renderer_id:

};
#endif