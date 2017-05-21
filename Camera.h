#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera {

	public:

		Camera( const glm::vec3& position, float fov, float aspect, float z_near, float z_far ) {\
			this->perspective = glm::perspective( fov, aspect, z_near, z_far );
			this->position = position;
			this->forward = glm::vec3( 0,0,1 );
			this->up = glm::vec3( 0,1,0 );
		};

		inline glm::mat4 GetViewProjection() const {
			return this->perspective * glm::lookAt( this->position, this->position + this->forward, this->up );
		}

		inline glm::vec3 GetPosition() const {
			return this->position;
		}
		
		
	protected:
	private:
		glm::mat4 perspective;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 up;
};

