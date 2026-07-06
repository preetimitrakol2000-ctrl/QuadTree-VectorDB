#ifndef QUADTREE_VECTOR_H
#define QUADTREE_VECTOR_H

typedef struct SpatialPoint SpatialPoint;
typedef struct QuadNode QuadNode;

QuadNode* init_quad_node(float mix, float miy, float max, float may);
bool insert_spatial_point(QuadNode* node, float x, float y, int id);
int query_spatial_point(QuadNode* node, float x, float y);

#endif
