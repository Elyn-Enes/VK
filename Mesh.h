#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "ObjLoader.h"
#include "ObjectLoader.h";
#include "Transform.h"
#include "Shader.h"

class Vertex {
	public:

		Vertex( const glm::vec3& position, const glm::vec2& texture_coord, const glm::vec3& normal = glm::vec3( 0,0,0 ) ) {
			this->position = position;
			this->texture_coord = texture_coord;
			this->normal = normal;
		}

		inline glm::vec3* GetPos() { return &this->position; }
		inline glm::vec2* GetTexCoord() { return &this->texture_coord; }
		inline glm::vec3* GetNormal() { return &this->normal; }

	protected:
	private:
		glm::vec3 position;
		glm::vec2 texture_coord;
		glm::vec3 normal;
};

class Mesh {

	public:

		Shader* shader = NULL;
		Transform transform;
		Mesh( Vertex* vertices, unsigned int vertice_count, unsigned int* indices, unsigned int indice_count );
		Mesh( const std::string& filename );
		Mesh( ObjectLoader obj );
		void Draw();
		virtual ~Mesh();

	protected:
	private:

		Mesh( const Mesh& other );
		void operator=( const Mesh& other );
		void InitMesh( const IndexedModel& model );

		enum {
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,
			NUM_BUFFERS
		};

		GLuint transform_vb;

		GLuint vertexArrayObject;
		GLuint vertexArrayBuffers[ NUM_BUFFERS ];
		unsigned int drawCount;

};

