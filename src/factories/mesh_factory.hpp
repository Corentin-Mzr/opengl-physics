#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "entity_config.hpp"

/*
Class that handles the creation of a model/mesh
*/
class MeshFactory
{

public:
    /*
    Create a mesh or return an existing one
    @param object_type: Type of the mesh (static_cast<unsigned>(ObjectType))
    */
    [[nodiscard]] Mesh load_mesh(const unsigned object_type);

private:
    /*
    Load a mesh using a file and store it in the mesh map
    @param filepath: Path to the mesh file (.obj)
    @param object_type: Type of object
    */
    [[nodiscard]] Mesh load_mesh_from_file(const char *filepath, const unsigned object_type);

    /*
    Process every node
    @param node: Node object
    @param scene: Scene related to the mesh
    @param object_type: Type of the object
    @param positions: Stores positions of all vertices
    @param uvs: Stores UV coords of all vertices
    @param normals: Stores normals of all vertices
    */
    void process_node(const aiNode *node, const aiScene *scene,
                      const unsigned object_type,
                      std::vector<float> &positions,
                      std::vector<float> &uvs,
                      std::vector<float> &normals);

    /*
    Process the mesh
    @param mesh: The mesh
    @param positions: Stores positions of all vertices
    @param uvs: Stores UV coords of all vertices
    @param normals: Stores normals of all vertices
    */
    void process_mesh(const aiMesh *mesh,
                      std::vector<float> &positions,
                      std::vector<float> &uvs,
                      std::vector<float> &normals);

    /*
    Reserve space to arrays based on the mesh data
    @param mesh: The mesh
    @param positions: Stores positions of all vertices
    @param uvs: Stores UV coords of all vertices
    @param normals: Stores normals of all vertices
    */
    void reserve_space(const aiMesh *mesh,
                       std::vector<float> &positions,
                       std::vector<float> &uvs,
                       std::vector<float> &normals);

    /*
    Fill the position array and normalize
    @param mesh: The mesh
    @param i: Current index
    @param positions: Array to fill
    */
    void fill_pos_array(const aiMesh *mesh, const size_t i, std::vector<float> &positions);

    /*
    Fill the UV array
    @param mesh: The mesh
    @param i: Current index
    @param uvs: Array to fill
    */
    void fill_uv_array(const aiMesh *mesh, const size_t i, std::vector<float> &uvs);

    /*
    Fill the normal array
    @param mesh: The mesh
    @param i: Current index
    @param uvs: Array to fill
    */
    void fill_normal_array(const aiMesh *mesh, const size_t i, std::vector<float> &normals);

    /*
    Create a mesh using the given data and store it in the mesh map
    @param positions: Array containing positions of vertices
    @param uvs: Array containing the uv coords of vertices
    @param normals: Array containing the normals of vertices
    */
    [[nodiscard]] Mesh create_mesh(const std::vector<float> &positions,
                                   [[maybe_unused]] const std::vector<float> &uvs,
                                   [[maybe_unused]] const std::vector<float> &normals);
};