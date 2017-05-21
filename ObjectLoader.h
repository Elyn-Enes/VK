#pragma once

#include <unordered_map>
#include <vector>
#include <objloader/objloader.h>
#include <string>
#include "VKVertex.h"

class ObjectLoader {

	public:

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		std::vector<uint32_t> indices;
		std::vector<VKVertex> vertices;



		ObjectLoader::ObjectLoader( const std::string obj_file ) {
		
			if ( ! tinyobj::LoadObj(&attrib, &shapes, &materials, &err, obj_file.c_str(), NULL, true ) ) {
				throw std::runtime_error(err);
			}

			std::unordered_map<VKVertex, uint32_t> uniqueVertices = {};
			for (const auto& shape : shapes) {
				for (const auto& index : shape.mesh.indices) {
					VKVertex vertex = {};

					vertex.pos = {
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],
						attrib.vertices[3 * index.vertex_index + 2]
					};

					vertex.normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2]
					};
			
					vertex.texCoord = {
						attrib.texcoords[2 * index.texcoord_index + 0],
						1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
					};

					vertex.color = {1.0f, 1.0f, 1.0f};

					if (uniqueVertices.count(vertex) == 0) {
						uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
						vertices.push_back(vertex);
					}

					indices.push_back(uniqueVertices[vertex]);

					
				}

			}

		}

};