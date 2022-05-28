author dterletskiy



data navigation
{
   version 1.2.3;

   field: string name;
   field: size_t id;

   method: string convert( size_t id );

   struct Tile
   {
      field: size_t id;
      field: string name;

      method: string convert( size_t id );
   };

   method: string convert( Tile tile, size_t id );

   field: vector< Tile > tiles;
}
