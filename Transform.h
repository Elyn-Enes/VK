#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform {

	public:

		Transform( const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3( 1.0, 1.0, 1.0 ) ) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
		};

		void Bind( unsigned int unit );

		inline glm::mat4 GetModel() const {

			glm::mat4 position_matrix = glm::translate( this->position );
			glm::mat4 rotation_x_matrix = glm::rotate( this->rotation.x, glm::vec3( 1,0,0 ) );
			glm::mat4 rotation_y_matrix = glm::rotate( this->rotation.y, glm::vec3( 0,1,0 ) );
			glm::mat4 rotation_z_matrix = glm::rotate( this->rotation.z, glm::vec3( 0,0,1 ) );
			glm::mat4 scale_matrix = glm::scale( this->scale );
			glm::mat4 rotation_matrix = rotation_z_matrix * rotation_y_matrix * rotation_x_matrix;

			return position_matrix * rotation_matrix * scale_matrix;

		}

		inline glm::vec3* GetPosition() { return &this->position; }
		inline glm::vec3* GetRotation() { return &this->rotation; }
		inline glm::vec3* GetScale() { return &this->scale; }

		inline void SetPosition( glm::vec3& position ) { this->scale = position; }
		inline void SetRotation( glm::vec3& rotation ) { this->scale = rotation; }
		inline void SetScale( glm::vec3& scale ) { this->scale = scale; }
		
		
	protected:
	private:

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform( const Transform& other ) {}


};

