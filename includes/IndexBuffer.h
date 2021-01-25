#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#pragma once
	
class IndexBuffer  {
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
	
		inline unsigned get_count() const;

	private:
		// OpenGL needs this as a type of ID for everything it creats
		// It is rendered_id, however, to keep it generic
		unsigned int m_renderer_id;
		// Need to know how many indices it has
		unsigned int m_count;


};
#endif