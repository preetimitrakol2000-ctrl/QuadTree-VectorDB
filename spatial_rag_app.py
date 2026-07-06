from quad_bridge import QuadBridge

if __name__ == "__main__":
    spatial_db = QuadBridge()

    # Map contextual entries across grid sectors (e.g., regional IoT telemetry documents)
    spatial_db.load_spatial_chunk(coord_x=12.5, coord_y=45.2, document_id=3001)
    spatial_db.load_spatial_chunk(coord_x=85.1, coord_y=90.4, document_id=3002)

    # Search directly for coordinates matching targeted metrics grids
    matched_id = spatial_db.locate_spatial_chunk(coord_x=12.5, coord_y=45.2)

    print("=== QUADTREE-VECTORDB REGIONAL COMPARTMENT SCANNER ===")
    print(f"[*] Navigated Grid Trees. Exact Sector Intersection Yielded Chunk ID: {matched_id}")
