#include "Mesh.h"
#include <vector>

Mesh::Mesh( const std::string& filename ) {
	IndexedModel model = OBJModel( filename ).ToIndexedModel();
	InitMesh( model );
}

Mesh::Mesh( Vertex* vertices, unsigned int vertice_count, unsigned int* indices, unsigned int indice_count ) {

	IndexedModel model;

	for ( unsigned int i = 0; i < vertice_count; i++ ) {
		model.positions.push_back( *vertices[ i ].GetPos() );
		model.texCoords.push_back( *vertices[ i ].GetTexCoord() );
		model.normals.push_back( *vertices[ i ].GetNormal() );
	}

	for ( unsigned int i = 0; i < indice_count; i++ ) {
		model.indices.push_back( indices[ i ] );
	}

	InitMesh( model );

}

Mesh::Mesh( ObjectLoader obj ) {

	IndexedModel model;

	for ( unsigned int i = 0; i < obj.vertices.size(); i++ ) {
		model.positions.push_back( obj.vertices[i].pos );
		model.texCoords.push_back( obj.vertices[i].texCoord);
		model.normals.push_back( obj.vertices[i].normal );
	}

	for ( unsigned int i = 0; i < obj.indices.size(); i++ ) {
		model.indices.push_back( obj.indices[ i ] );
	}

	InitMesh( model );

}

void Mesh::InitMesh( const IndexedModel& model ) {

	this->drawCount = model.indices.size();
	
	glGenVertexArrays( 1, &this->vertexArrayObject );
	glBindVertexArray( this->vertexArrayObject );

	glGenBuffers( this->NUM_BUFFERS, this->vertexArrayBuffers );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->POSITION_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.positions.size() * sizeof( model.positions[0] ), &model.positions[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->TEXCOORD_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.positions.size() * sizeof( model.texCoords[0] ), &model.texCoords[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->NORMAL_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.normals.size() * sizeof( model.normals[0] ), &model.normals[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->vertexArrayBuffers[ this->INDEX_VB ] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, model.positions.size() * sizeof( model.indices[0] ), &model.indices[0], GL_STATIC_DRAW );

	glBindVertexArray( 0 );

}


Mesh::~Mesh(){
	glDeleteVertexArrays( 1, &this->vertexArrayObject );
}

void Mesh::Draw() {

	glBindVertexArray( this->vertexArrayObject );
	glDrawElements( GL_TRIANGLES, this->drawCount, GL_UNSIGNED_INT, 0 );
	//glDrawArrays( GL_TRIANGLES, 0, this->drawCount );
	glBindVertexArray(0);
}