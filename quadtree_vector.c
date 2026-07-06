#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
    int chunk_id;
} SpatialPoint;

typedef struct QuadNode {
    float min_x, min_y, max_x, max_y;
    SpatialPoint* point;
    struct QuadNode* children[4]; // NW, NE, SW, SE
    bool is_divided;
} QuadNode;

#ifdef _WIN32
    __declspec(dllexport) QuadNode* init_quad_node(float mix, float miy, float max, float may);
    __declspec(dllexport) bool insert_spatial_point(QuadNode* node, float x, float y, int id);
    __declspec(dllexport) int query_spatial_point(QuadNode* node, float x, float y);
#endif

QuadNode* init_quad_node(float mix, float miy, float max, float may) {
    QuadNode* node = (QuadNode*)malloc(sizeof(QuadNode));
    node->min_x = mix; node->min_y = miy;
    node->max_x = max; node->max_y = may;
    node->point = NULL;
    node->is_divided = false;
    for (int i = 0; i < 4; i++) node->children[i] = NULL;
    return node;
}

void split_node(QuadNode* node) {
    float mid_x = (node->min_x + node->max_x) / 2.0f;
    float mid_y = (node->min_y + node->max_y) / 2.0f;

    node->children[0] = init_quad_node(node->min_x, mid_y, mid_x, node->max_y);       // NW
    node->children[1] = init_quad_node(mid_x, mid_y, node->max_x, node->max_y);       // NE
    node->children[2] = init_quad_node(node->min_x, node->min_y, mid_x, mid_y);       // SW
    node->children[3] = init_quad_node(mid_x, node->min_y, node->max_x, mid_y);       // SE
    node->is_divided = true;
}

bool insert_spatial_point(QuadNode* node, float x, float y, int id) {
    if (x < node->min_x || x > node->max_x || y < node->min_y || y > node->max_y) return false;

    if (node->point == NULL && !node->is_divided) {
        node->point = (SpatialPoint*)malloc(sizeof(SpatialPoint));
        node->point->x = x; node->point->y = y;
        node->point->chunk_id = id;
        return true;
    }

    if (!node->is_divided) split_node(node);

    for (int i = 0; i < 4; i++) {
        if (insert_spatial_point(node->children[i], x, y, id)) return true;
    }
    return false;
}

int query_spatial_point(QuadNode* node, float x, float y) {
    if (x < node->min_x || x > node->max_x || y < node->min_y || y > node->max_y) return -1;
    if (node->point != NULL) return node->point->chunk_id;
    if (!node->is_divided) return -1;

    for (int i = 0; i < 4; i++) {
        int res = query_spatial_point(node->children[i], x, y);
        if (res != -1) return res;
    }
    return -1;
}
