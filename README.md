# engine

2D SFML game "engine" of sorts.

## stuff

- Tile-based maps
- update() method like Unity
- Component-like things (coming soon)
- It works

## limitations

- Map tilesets can only contain a maximum of 255 tiles (about 16x16), because the map format currently only allocates 1 byte for the tile index
- Engine will crash with a segfault if a non-existent texture is loaded

## building

1. Clone the repo (I can't believe you have to explicitly tell GitHub Actions this. otherwise it just runs in an empty repo)
2. Install [Cate](https://github.com/TheMilkies/Cate)
3. Install SFML (`libsfml-dev` for apt)
4. Run `cate` in the project root
5. Find the executable in `out/`
