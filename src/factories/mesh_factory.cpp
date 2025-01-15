#include "mesh_factory.hpp"

/*
Create a mesh
@param object_type: Type of the mesh
*/
Mesh MeshFactory::load_mesh(const unsigned object_type)
{
    Mesh mesh = load_mesh_from_file(model_names[object_type], object_type);

    // Check
    if (mesh.vertex_count != 0 && mesh.vao != 0)
    {
        std::cout << "[MESH FACTORY LOADING SUCCESS] "
                  << "Mesh " << model_names[object_type] << " has been loaded\n";
    }
    else
    {
        std::cerr << "[MESH FACTORY LOADING ERROR] "
                  << "Mesh " << model_names[object_type] << " was not loaded properly\n";
    }

    return mesh;
}

/*
Load a mesh using a file
@param filepath: Path to the mesh file (.obj)
*/
Mesh MeshFactory::load_mesh_from_file(const char *filepath, const unsigned object_type)
{
    std::cout << "[MESH FACTORY LOADING INFO] Trying to load " << filepath << std::endl;

    // Load the model with Assimp
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Check for loading erros
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "[MESH FACTORY LOADING ERROR] " << import.GetErrorString() << std::endl;
    }

    // Store directory (will be used for texture loading)
    const std::string filepath_as_str = std::string(filepath);
    const std::string directory = filepath_as_str.substr(0, filepath_as_str.find_last_of('/'));

    // Process node
    std::vector<float> positions, uvs, normals;

    // Store loaded mesh (directly in the map so that we dont use intermediate variables that would destroy the object)
    process_node(scene->mRootNode, scene, object_type, positions, uvs, normals);

    return create_mesh(positions, uvs, normals);
}

/*
Process every node and store the mesh created
@param node: Node object
@param scene: Scene related to the mesh
@param filepath: Path to the mesh file (.obj)
@param positions: Stores positions of all vertices
@param uvs: Stores UV coords of all vertices
@param normals: Stores normals of all vertices
*/
void MeshFactory::process_node(const aiNode *node, const aiScene *scene,
                               const unsigned object_type,
                               std::vector<float> &positions,
                               std::vector<float> &uvs,
                               std::vector<float> &normals)
{
    // Process all node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(mesh, scene, positions, uvs, normals);
    }

    // Proces all children' meshes
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene, object_type, positions, uvs, normals);
    }
}

/*
Process the mesh
@param mesh: The mesh
@param scene: Scene related to the mesh
@param positions: Stores positions of all vertices
@param uvs: Stores UV coords of all vertices
@param normals: Stores normals of all vertices
*/
void MeshFactory::process_mesh(const aiMesh *mesh, const aiScene *scene,
                               std::vector<float> &positions,
                               std::vector<float> &uvs,
                               std::vector<float> &normals)
{
    reserve_space(mesh, positions, uvs, normals);

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        fill_pos_array(mesh, i, positions);
        fill_uv_array(mesh, i, uvs);
        fill_normal_array(mesh, i, normals);
    }
}

/*
Reserve space to arrays based on the mesh data
@param mesh: The mesh
@param positions: Stores positions of all vertices
@param uvs: Stores UV coords of all vertices
@param normals: Stores normals of all vertices
*/
void MeshFactory::reserve_space(const aiMesh *mesh,
                                std::vector<float> &positions,
                                std::vector<float> &uvs,
                                std::vector<float> &normals)
{
    size_t p_reserve = positions.size() + 3 * mesh->mNumVertices;
    size_t u_reserve = uvs.size() + 2 * mesh->mNumVertices;
    size_t n_reserve = normals.size() + 3 * mesh->mNumVertices;

    if (p_reserve > 0)
        positions.reserve(p_reserve);
    if (u_reserve > 0)
        uvs.reserve(u_reserve);
    if (n_reserve > 0)
        normals.reserve(n_reserve);
}

/*
Fill the position array and normalize
@param mesh: The mesh
@param i: Current index
@param positions: Array to fill
*/
void MeshFactory::fill_pos_array(const aiMesh *mesh, const size_t i, std::vector<float> &positions)
{
    const float length = mesh->mVertices->Length() != 0 ? mesh->mVertices->Length() : 1.0f;
    positions.push_back(mesh->mVertices[i].x / length);
    positions.push_back(mesh->mVertices[i].y / length);
    positions.push_back(mesh->mVertices[i].z / length);
}

/*
Fill the UV array
@param mesh: The mesh
@param i: Current index
@param uvs: Array to fill
*/
void MeshFactory::fill_uv_array(const aiMesh *mesh, const size_t i, std::vector<float> &uvs)
{
    // check if UV coords exist
    if (mesh->mTextureCoords[0])
    {
        uvs.push_back(mesh->mTextureCoords[0][i].x);
        uvs.push_back(mesh->mTextureCoords[0][i].y);
    }
    else
    {
        uvs.push_back(0.0f);
        uvs.push_back(0.0f);
    }
}

/*
Fill the normal array
@param mesh: The mesh
@param i: Current index
@param uvs: Array to fill
*/
void MeshFactory::fill_normal_array(const aiMesh *mesh, const size_t i, std::vector<float> &normals)
{
    // Check if normals exists, else compute them
    if (mesh->mNormals)
    {
        normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);
    }
    else
    {
        aiVector3D normal{0.0f, 0.0f, 0.0f};
        // Calculate normals using the vertices for each face (triangle)
        if (mesh->mFaces)
        {
            // Get the indices of the vertices that make up the triangle
            unsigned int index1 = mesh->mFaces[i / 3].mIndices[0];
            unsigned int index2 = mesh->mFaces[i / 3].mIndices[1];
            unsigned int index3 = mesh->mFaces[i / 3].mIndices[2];

            // Get the positions of the three vertices in the triangle
            aiVector3D v1 = mesh->mVertices[index1];
            aiVector3D v2 = mesh->mVertices[index2];
            aiVector3D v3 = mesh->mVertices[index3];

            // Calculate the two edges of the triangle
            aiVector3D edge1 = v2 - v1;
            aiVector3D edge2 = v3 - v1;

            // Calculate the normal of the triangle using the cross product
            normal = edge1 ^ edge2;
            normal.Normalize();
        }
        else
            normal = aiVector3D(0.0f, 0.0f, 0.0f);

        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    }
}

/*
Create a mesh using the given data
@param positions: Array containing positions of vertices
@param uvs: Array containing the uv coords of vertices
@param normals: Array containing the normals of vertices
*/
[[nodiscard]] Mesh MeshFactory::create_mesh(const std::vector<float> &positions,
                                            const std::vector<float> &uvs,
                                            const std::vector<float> &normals)
{
    unsigned int vao, vbo_pos, vertex_count;

    // Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate VBO for Position and link to layout 0
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // // Generate VBO for UV Coords and link to layout 1
    // if (!uvs.empty())
    // {
    //     glGenBuffers(1, &vbo_uv);
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
    //     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    //     glEnableVertexAttribArray(1);
    // }

    // // Generate VBO for normals and link to layout 2
    // if (!normals.empty())
    // {
    //     glGenBuffers(1, &vbo_normals);
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);
    //     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //     glEnableVertexAttribArray(2);
    // }

    // UNBIND VAO
    glBindVertexArray(0);

    // Vertex count
    vertex_count = positions.size() / 3;

    // Store mesh
    return Mesh{vao, vbo_pos, 0, vertex_count};
}