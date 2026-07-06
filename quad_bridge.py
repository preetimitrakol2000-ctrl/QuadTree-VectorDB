import ctypes
import os
import sys

class QuadBridge:
    def __init__(self):
        if not os.path.exists("./libquad.so") and not os.path.exists("./libquad.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libquad.dll quadtree_vector.c")
                lib_path = "./libquad.dll"
            else:
                os.system("gcc -shared -fPIC -o libquad.so quadtree_vector.c")
                lib_path = "./libquad.so"
        else:
            lib_path = "./libquad.dll" if sys.platform.startswith("win") else "./libquad.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_quad_node.restype = ctypes.c_void_p
        self.lib.insert_spatial_point.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_int]
        self.lib.insert_spatial_point.restype = ctypes.c_bool
        self.lib.query_spatial_point.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
        self.lib.query_spatial_point.restype = ctypes.c_int
        
        # Instantiate coordinate index bounds from 0.0 to 100.0
        self.root_ptr = self.lib.init_quad_node(0.0, 0.0, 100.0, 100.0)

    def load_spatial_chunk(self, coord_x: float, coord_y: float, document_id: int):
        self.lib.insert_spatial_point(self.root_ptr, coord_x, coord_y, document_id)

    def locate_spatial_chunk(self, coord_x: float, coord_y: float) -> int:
        return self.lib.query_spatial_point(self.root_ptr, coord_x, coord_y)
